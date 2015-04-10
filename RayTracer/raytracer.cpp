/**
 * The RayTracer is multithreaded for performance; depending on the number of cores available,
 * decuded 
 */

#include <raytracer.h>
#include <QDebug>

RayTracer::RayTracer()
{
	//Add scene creation.
	this->sceneManager = new SceneManager();
    SceneGraphNode *root = new SceneGraphNode(NULL, NULL);
	this->sceneManager->root = root;

	SceneGraphNode *sphere = new SceneGraphNode(new Sphere(), new SceneObjectProperties());
    sphere->localTransform.scale(150);
	root->addChild(sphere);

    this->activeShader = new LambertShader();

    //Multi-Threading Infomation
    //We will zero the flags, then use the setters to set appropriate values and
    //the flag. This will ensure that on the first iteration, datastructures are
    //initialized. 
    this->dirtyFlags = 0x0000; 
    this->setWorkerCount(getNumCores()); 
    this->setRenderSize(width, height);
    
    qDebug() << "RayTracer: System reporting " << getNumCores() << " cores online.";
    //TODO: Create master worker thread and wait it on a Semaphore.
}

void RayTracer::setRenderSize(int width, int height)
{
    this->renderWidth = width;
    this->renderHeight = height;
    this->dirtyFlags |= 0x0001; //Dimensions Flag.
}

void RayTracer::setWorkerCount(int count)
{
    this->workerCount = count;
    this->dirtyFlags |= 0x4000;
}

void RayTracer::render_reconfigure()
{
    /*
     * Check that the active configuration of the render has not changed, if it has, update
     * the needed structures
     */
     //TODO: Lock on something. 
     if(this->dirtyFlags & FLAG_DIMENSIONS)
     {
        //Dimensions
        delete this->renderData;
        //Using RGBA, we need to account for the alpha channel.
        this->renderData = new unsigned char[this->renderWidth * this->renderHeight * 4];
        this->image(renderData, this->renderWidth, this->renderHeight,  QImage::Format_ARGB32_Premultiplied);
     }
     if(this->dirtyFlags & FLAG_WORKER_COUNT)
     {
        if(this->workers.size() < this->renderThreadCount)
        {
            int toInsert = this->renderThreadCount - this->workers.size();
            for(int i - 0; i < toInsert; i++)
            {
                this->workers.push_back(new std::thread(&RayTracer::renderWorker, this));
            }
        }
     }
}

void RayTracer::render_master()
{
    //Local copies of system parameters to ensure that we don't run into issues. 
    int width, height, workerCount;
    std::thread *t; 
    int i;

    while(!this->dirtyFlags & FLAG_EXIT)
    {
        //Ensure we're up to date with our configuration. 
        if(this->dirtyFlags)
        {
            /* reconfigure any needed data structures */
            this->render_reconfigure();
            width = this->renderWidth;
            height = this->renderHeight;
            workerCount = this->renderThreadCount;
        }

        //Perform standard iteration resets;
        this->nextPixel = 0;

        //TODO: Ensure we are not in paused state.

        //Everything is in order. Run an iteration. 
        for(i = 0; i < workerCount; i++)
        {
            //TODO: Release semaphore token for each worker. 
        }
        //TODO: WAIT until all workers have started.
        
        //TODO: Wait for workers to finish/pause.

        //TODO: Signal UI to repaint. 
    }
    
    // If we have reached this point, we are heading to 
    // termination, 
    // Start Clean up 
    // //////////////////////////////////////////

    //Each of the workers is to exit when it completes a pixel and detects the flag set
    //to quit the application. 
    for (int i = 0; i < workerCount; i++)
    {
        t = workers.pop_back();
        t->join();
        delete t;
    }

    //TODO: Send signal to repaint the image. I'm interested to see if there is any issue given
    //      the operations of changing colours are mostly atomic. Some pixels perhaps will have
    //      odd colours but will it be noticable at a high enough frame rate?
    

}


void RayTracer::render_worker()
{
    /*
     * Each worker operates on a different portion of the image dta, so no thread control 
     * mechanism to ensure mutual exclusion is needed.  
     */
    QVector3D colour;
    // TODO: CAMERA CONTROLS
    Ray* ray = new Ray(QVector3D(0,0,800), QVector3D(0,0,-1))
    CastResult cr = new CastResult()
    unsigned char* ptr;
    uint x, y;
    uint pix;
    //We want to run as a worker until either the cancel flag is set, or the image
    //has been entirely populated. 
    while (!this->dirtyFlags & FLAG_EXIT)
    {
        pix = ++(this->nextPixel) //Maybe i'm over thinking how the volatile keyword works.
        pix -= 1;

        if (pix >= this->renderHeight * this->renderWidth)
            break;

        x = pix % this->renderWidth;
        y = (int)(pix / this->renderWidth);
        ptr = this->renderData + (this->renderBPL*y) + (x*4);

        colour = getPixel(ray, cr, x+i, y+j);
        *(p++) = max(0, min(colour.x() * 255, 255));
        *(p++) = max(0, min(colour.y() * 255, 255));
        *(p++) = max(0, min(colour.z() * 255, 255));
        *(p++) = ~0;
    }
    //The work of the worker is done, it has completed its section of the image. 
    //The RayTracer will build an image from the data in the array provided to
    //this worker.
}

QVector3D RayTracer::getPixel(Ray* ray, CastResult* cr, int x, int y)
{
    /* this helper with fetch the colour of a pixel in the scene. */
    /* if there are to be expansions on rendering, such as jitter, it will 
    go in here */

    QVector3D result;
    //ray.setToPerspectiveRay(focalLength, renderWidth, renderHeight, x, y);
    ray.setToOrthographicRay(cameraFocalLength, renderWidth, renderHeight, x, y);
    if(this->sceneManager->root->castRay(ray, QMatrix4x4(), cr))
    {
        //If we have hit something that is ahead of our vision plane, use
        //the currently shader model to determine pixel colour.
        result += this->activeShader->getPixelColour(cr->surfacePoint,
           cr->surfaceNormal, cr->subject->getMaterial(), this->sceneLight) ;
    }
    else
    {
        //We didn't hit anything in the scene! Use a background colour
        //of dark grey to indicate this.
        result += QVector3D(0.3,0.3,0.3);
    }
    return result;
}



QImage RayTracer::render(int width, int height)
{
    qDebug() << "RayTracer: Starting render of size " << width << "x" << height;
    double start = std::clock();
    //TODO: Incorporate Camera Controls.
    //Default Camera, out along the Z axis, looking back at origin
    Ray ray(QVector3D(0, 0, 800), QVector3D(0,0,-1).normalized());

    //TODO Allow multiple lights.
    LightSource * light = new LightSource();
    CastResult* castresult = new CastResult();
	QVector3D pixelColour;
    QImage result = QImage(width, height, QImage::Format_RGB32);
	
    double focalLength = 1; //Does not matter for the moment as we use Orthogonal rays.

    //renderLauncher

    qDebug() << "RayTracer: Render completed in " << (std::clock() - start) / CLOCKS_PER_SEC << "seconds.";
	return result;
}


