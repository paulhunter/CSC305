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

    Sphere *s = new Sphere(), 
    sphere->localTransform.scale(150);
    this->sceneManager->add_sceneObject(s, new SceneObjectProperties());

    this->activeShader = new LambertShader();

    //Multi-Threading Infomation
    //We will zero the flags, then use the setters to set appropriate values and
    //the flag. This will ensure that on the first iteration, datastructures are
    //initialized. 
    this->dirtyFlags = 0x0000; 
    this->setWorkerCount(getNumCores()); 
    this->setRenderSize(1, 1);

    this->workTokens = 0;
    
    qDebug() << "RayTracer: System reporting " << getNumCores() << " cores online.";
    //TODO: Create master worker thread and wait it on a Semaphore.
}

void RayTracer::setRenderSize(int width, int height)
{
    this->managedInterfaceLock.lock();
    this->renderWidth = width;
    this->renderHeight = height;
    this->dirtyFlags |= 0x0001; //Dimensions Flag.
    this->managedInterfaceLock.unlock();
}

void RayTracer::setWorkerCount(int count)
{
    this->managedInterfaceLock.lock();
    this->workerCount = count;
    this->dirtyFlags |= 0x4000; //Thread count adjustment
    this->managedInterfaceLock.unlock();
}

void RayTracer::render_reconfigure()
{
    /*
     * Check that the active configuration of the render has not changed, if it has, update
     * the needed structures
     *
     * The Render Master calls this method, and should lock on the managed interface lock
     * before entering the method. Afterwards it should, as it currently done, sample the
     * settings for their own mathematical calculations. 
     */

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
    /* Render Master Thread Work
     * 
     * The Render Master thread is responsible for coordinating the workers in 
     * the rendering of a single frame. This is done using a counter for the number 
     * of work tokens which are distributed to and returned by the workers by 
     * the master. 
     */
    //Local copies of system parameters to ensure that we don't run into issues. 
    int i;
    
    //RenderLoop
    while(!this->dirtyFlags & FLAG_EXIT)
    {
        //Ensure we're up to date with our configuration. 
        if(this->dirtyFlags)
        {
            //Lock out any other threads which maybe doing setting of variables
            this->managedInterfaceLock.lock();
            /* reconfigure any needed data structures */
            this->render_reconfigure();
            this->_width = this->renderWidth;
            this->_height = this->renderHeight;
            this->renderBPL = this->renderWidth * this->renderHeight * 4;
            this->_workerCount = this->renderThreadCount;

            // Unlock to allow outside modification before the next iteration. 
            this->managedInterfaceLock.unlock();
        }

        //Perform standard iteration resets;
        this->nextPixel = 0;

        //TODO: Ensure we are not in paused state.

        //Everything is in order. Run an iteration. 

        //Distribute a number of tokens for workers.
        std::unique_lock<std::mutex> worklk(this->workSemaMux);
        this->workTokens = workerCount; 

        //We could notify each thread individiually, but only workerCount of them
        //can be awoken as that is the allocated number of takens, so we can awaken
        //all of them and let them fight for a token.
        this->workSema.notify_all();
        worklk.unlock();

        //At this point, each otherkers has been placed in a ready state to try for
        //the lock on the work mutex. As they wake and each will decriment the work 
        //tokens and release the lock themselves, carrying on to work. When they finish
        //the image they will each decremenet a second time. 

        //Now the master needs to wait to ensure all workers started
        while(this->workTokens > 0); //Spin wait, we dont expect it to be long. 
            //DEBUG: Can print to indicate number of workers started as expected.

        //Wait for each of the workers to finish. When they do each of them will
        //decrement the work tokens counter another time, so when all workers
        //finished  
        worklk.lock();
        while(this->workTokens > -this->workerCount) this->workSema.wait(lk);
        this->workTokens = 0;
        worklk.unlock(); //The lock would go out of scope and unlock at the end of the iteration
                         //but i dont think we need to hang on to it past this point.

        

        //TODO: Send signal to repaint the image. I'm interested to see if there is any issue given
        //      the operations of changing colours are mostly atomic. Some pixels perhaps will have
        //      odd colours but will it be noticable at a high enough frame rate?
    }
    
    // If we have reached this point, we are heading to 
    // termination, 
    // Start Clean up 
    // //////////////////////////////////////////

    //Each of the workers is to exit when it completes a pixel and detects the flag set
    //to quit the application. 
    for (int i = 0; i < this->_workerCount; i++)
    {
        t = this->workers.pop_back();
        t->join();
        delete t;
    }
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
        //Instantiation of the lock with this constructor will lock the mutex. 
        std::unique_lock<std::mutex> worklk = worklk(this->workSemaMux);
        while(this->workToken <= 0) this->workSema.wait(worklk);
        this->workToken--;
        worklk.unlock()

        while (this->nextPixel < this->_height * this->_width)
        {    
            pix = ++(this->nextPixel) //Maybe i'm over thinking how the volatile keyword works.
            pix -= 1;


            x = pix % this->_width;
            y = (int)(pix / this->_width);
            ptr = this->renderData + (this->renderBPL*y) + (x*4);

            colour = getPixel(ray, cr, x, y);
            *(p++) = max(0, min(colour.x() * 255, 255));
            *(p++) = max(0, min(colour.y() * 255, 255));
            *(p++) = max(0, min(colour.z() * 255, 255));
            *(p++) = ~0;
        }

        //Inidicate that we have finished and return to await another signal to
        //start processing.
        worklk.lock();
        this->workToken--;
        worklk.unlock();
        //There is a chance that other threads have been created but the 
        //number of workers has been reduced, they are still waiting on
        //conditional variable, so we notify all to ensure we do awaken
        //the master thread.
        this->workSema.notify_all(); 

        //The work of the worker is done, it has completed its section of the image. 
        //The RayTracer will build an image from the data in the array provided to
        //this worker.   
    }
}

QVector3D RayTracer::getPixel(Ray* ray, CastResult* cr, int x, int y)
{
    /* this helper with fetch the colour of a pixel in the scene. */
    /* if there are to be expansions on rendering, such as jitter, it will 
    go in here */

    QVector3D result;
    //ray.setToPerspectiveRay(focalLength, renderWidth, renderHeight, x, y);
    ray.setToOrthographicRay(cameraFocalLength, renderWidth, renderHeight, x, y);
    if(this->sceneManager->castRay(ray, cr))
    {
        //If we have hit something that is ahead of our vision plane, use
        //the currently shader model to determine pixel colour.
        result += this->activeShader->getPixelColour(cr->surfacePoint,
           cr->surfaceNormal, cr->subjectProperties, this->sceneLight) ;
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


