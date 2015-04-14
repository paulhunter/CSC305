/**
 * The RayTracer is multithreaded for performance; depending on the number of cores available,
 * decuded 
 */

#include "raytracer.h"
#include "utils.h"
#include "math.h"
#include <QDebug>
#include <stdio.h>
#include "unistd.h"

#define MAX_THREADS_P 16
#define SAMPLE_SIZE 5

RayTracer::RayTracer()
{
	// //////////////////////////////////////////////////////////////////////
    // SCENE CREATION 
    // Room with three walls, left, back, and right. 
    // A ground plane.
    // Three Spheres within the room of various size and material.
    // //////////////////////////////////////////////////////////////////////
	this->sceneManager = new SceneManager();

    /*Shiny Big Sphere */
    SceneObject* silverSphere = SceneObjectFactory::getInstance().createSceneObject_wScale(PrimitiveShape::SPHERE, QVector3D(0,10,5), 2); //QVector3D(0, 5, -5), 2);
    this->sceneManager->add_sceneObject(silverSphere, MaterialsFactory::getMaterial(MaterialsFactory::INDIGO_FLAT));

    /* Orange Back Sphere */
    SceneObject* orangeSphere = SceneObjectFactory::getInstance().createSceneObject_wScale(PrimitiveShape::SPHERE, QVector3D(0, 1, 0), 10);
    this->sceneManager->add_sceneObject(orangeSphere, MaterialsFactory::getMaterial(MaterialsFactory::ORANGE_FLAT));

    /* Copper front sphere */ //Currently yellow
    SceneObject* copperSphere = SceneObjectFactory::getInstance().createSceneObject_wScale(PrimitiveShape::SPHERE, QVector3D(15, 3, 5), 1.0);
    this->sceneManager->add_sceneObject(copperSphere, MaterialsFactory::getMaterial(MaterialsFactory::YELLOW_FLAT));

    /* Ground Plane */
    SceneObject* groundPlane = SceneObjectFactory::getInstance().createSceneObject(PrimitiveShape::PLANE, QVector3D(0,0,0));
    this->sceneManager->add_sceneObject(groundPlane, MaterialsFactory::getMaterial(MaterialsFactory::GREY_LIGHT_FLAT));

    /* Red Back Wall */
    SceneObject* leftWall = SceneObjectFactory::getInstance().createSceneObject_wRot(PrimitiveShape::PLANE, QVector3D(-100, 0, 0), 90, 0, 0);
    this->sceneManager->add_sceneObject(leftWall, MaterialsFactory::getMaterial(MaterialsFactory::RED_FLAT));

    /* White Corner Scene Light */
    SceneObject* sceneLight = SceneObjectFactory::getInstance().createSceneObject(PrimitiveShape::SPHERE, QVector3D(-25, 50, 15));
    this->sceneManager->add_lightSource(sceneLight, MaterialsFactory::getMaterial(MaterialsFactory::LIGHT_WHITE));

    SceneObject* sceneLight2 = SceneObjectFactory::getInstance().createSceneObject(PrimitiveShape::SPHERE, QVector3D(25, 50, 15));
    this->sceneManager->add_lightSource(sceneLight2, MaterialsFactory::getMaterial(MaterialsFactory::LIGHT_WHITE));

    SceneObject* sceneLight3 = SceneObjectFactory::getInstance().createSceneObject(PrimitiveShape::SPHERE, QVector3D(0, 10, 50));
    this->sceneManager->add_lightSource(sceneLight3, MaterialsFactory::getMaterial(MaterialsFactory::LIGHT_WHITE));


    // END OF SCENE CREATION

    this->activeShader = new LambertShader();

    this->sampleResolution = SAMPLE_SIZE;
    for(int i = 0; i < this->sampleResolution*this->sampleResolution; i++)
    {
        this->jitterValues.push_back((double)std::rand()/RAND_MAX);
    }

    //Multi-Threading Infomation
    //Setup the control mechanisms.
    pthread_mutex_init(&(this->managedInterfaceLock), NULL);
    pthread_mutex_init(&(this->workTokensMux), NULL);
    pthread_cond_init(&(this->workTokensCond), NULL);
    pthread_attr_init(&(this->workerAttr));
    pthread_attr_setstacksize(&(this->workerAttr), 1024);

    //We will zero the flags, then use the setters to set appropriate values and
    //the flag. This will ensure that on the first iteration, datastructures are
    //initialized. 
    this->dirtyFlags = 0x0000; 
    this->renderData = NULL;
    this->setWorkerCount(MAX_THREADS_P);
    this->setRenderSize(600, 600);

    this->workTokens = 0;
    
    qDebug() << "RayTracer: System reporting " << getNumCores() << " cores online.";
    //TODO: Create master worker thread and wait it on a Semaphore.
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    int s = pthread_create(&(this->master), NULL, RayTracer::render_master_dummy, this);
    if (s != 0)
    {
        qDebug() << "RayTracer: Unable to start master!";
    }
    else
    {
        qDebug() << "RayTracer: Started";
    }
}

/* PUBLIC SETTINGS SETTERS */
void RayTracer::setRenderSize(int width, int height)
{
    pthread_mutex_lock(&(this->managedInterfaceLock));
    this->renderWidth = width;
    this->renderHeight = height;
    this->dirtyFlags |= FLAG_DIMENSIONS; //Dimensions Flag.
    pthread_mutex_unlock(&(this->managedInterfaceLock));
}

void RayTracer::setWorkerCount(int count)
{
    if (count > MAX_THREADS_P) count = MAX_THREADS_P;
    pthread_mutex_lock(&(this->managedInterfaceLock));
    qDebug() << "RayTracer: Worker Count set to " << count << ".";
    this->renderThreadCount = count;
    this->dirtyFlags |= FLAG_WORKER_COUNT; //Thread count adjustment
    pthread_mutex_unlock(&(this->managedInterfaceLock));
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
        if(this->renderData != NULL)
            delete this->renderData;

        //Using RGBA, we need to account for the alpha channel.
        this->renderData = new unsigned char[this->renderWidth * this->renderHeight * 4];
        qDebug() << "Image has " << this->renderWidth * this->renderHeight * 4 << "bytes.";
        this->image = new QImage(renderData, this->renderWidth, this->renderHeight,  QImage::Format_ARGB32_Premultiplied);
    }

     if(this->dirtyFlags & FLAG_WORKER_COUNT > 0)
     {
        if(this->workers == NULL)
        {
            qDebug() << "Creating Worker list for first time.";
            pthread_attr_t attr;
            pthread_attr_init(&attr);
            pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
            this->workers = (pthread_t*)calloc(MAX_THREADS_P, sizeof(pthread_t));
            if (this->workers == NULL)
            {
                qDebug() << "ERROR CREATING THREAD LIST!";
            }
            else
            {
                qDebug() << "Thread List created";
            }
            for(int i = 0; i < MAX_THREADS_P; i++)
            {
                pthread_create(&(this->workers[i]), NULL, RayTracer::render_worker_dummy, this);
            }
        }
     }
}

void* RayTracer::render_master_dummy(void * ptr)
{
    /* this is the nasty work around for pthreads lack of support object contexts */
    (static_cast<RayTracer*>(ptr))->render_master();
    pthread_exit(NULL);
    return 0;
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
    qDebug() << "RayTracer: Master Thread Started";
    uint iterations = 0;
    clock_t start;
    
    //RenderLoop
    while(1 || !(this->dirtyFlags & FLAG_EXIT > 0))
    {

        //Ensure we're up to date with our configuration. 
        if(this->dirtyFlags)
        {
            qDebug() << "RayTracer: Re-configuring.";
            //Lock out any other threads which maybe doing setting of variables
            pthread_mutex_lock(&(this->managedInterfaceLock));
            /* reconfigure any needed data structures */
            this->render_reconfigure();
            this->_width = this->renderWidth;
            this->_height = this->renderHeight;
            this->renderBPL = this->renderWidth * 4;
            this->_workerCount = this->renderThreadCount;

            // Unlock to allow outside modification before the next iteration. 
            this->dirtyFlags = 0;
            pthread_mutex_unlock(&(this->managedInterfaceLock));
        }

        //Perform standard iteration resets;
        iterations += 1;
        this->nextPixel = 0;

        //TODO: Ensure we are not in paused state?

        //Everything is in order. Run an iteration. 
        qDebug() << "RayTracer: Starting Iteration " << iterations << ".";
        start = clock();
        //Distribute a number of tokens for workers.
        qDebug() << "RayTracer: Distributing " << this->_workerCount << "work tokens.";
        pthread_mutex_lock(&(this->workTokensMux));
        this->workTokens = this->_workerCount;

        //We could notify each thread individiually, but only workerCount of them
        //can be awoken as that is the allocated number of takens, so we can awaken
        //all of them and let them fight for a token.
        pthread_cond_broadcast(&(this->workTokensCond));
        pthread_mutex_unlock(&(this->workTokensMux));
        usleep(1000000);
        qDebug() << "RayTracer: Tokens Sent.";



        //At this point, each otherkers has been placed in a ready state to try for
        //the lock on the work mutex. As they wake and each will decriment the work 
        //tokens and release the lock themselves, carrying on to work. When they finish
        //the image they will each decremenet a second time. 

        //Now the master needs to wait to ensure all workers started
        while(this->workTokens > 0) { pthread_cond_signal(&(this->workTokensCond)); } //Spin wait, we dont expect it to be long.
            //DEBUG: Can print to indicate number of workers started as expected.
        qDebug() << "RayTracer: All work tokens consumed. Waiting for completion.";

        //Wait for each of the workers to finish. When they do each of them will
        //decrement the work tokens counter another time, so when all workers
        //finished  
        pthread_mutex_lock(&(this->workTokensMux));
        while(this->workTokens > -this->_workerCount) pthread_cond_wait(&(this->workTokensCond), &(this->workTokensMux));
        this->workTokens = 0;
        pthread_mutex_unlock(&(this->workTokensMux)); //The lock would go out of scope and unlock at the end of the iteration
                         //but i dont think we need to hang on to it past this point.

        //qDebug() << "RayTracer: Render Complete (" << clock() - start << " seconds).";

        //TODO: Send signal to repaint the image. I'm interested to see if there is any issue given
        //      the operations of changing colours are mostly atomic. Some pixels perhaps will have
        //      odd colours but will it be noticable at a high enough frame rate?

        break; //Run only one iteration.
    }
    
    qDebug() << "RayTracer: Master Thread starting Termination Process.";

    // If we have reached this point, we are heading to 
    // termination, 
    // Start Clean up 
    // //////////////////////////////////////////


    //Each of the workers is to exit when it completes a pixel and detects the flag set
    //to quit the application. 
    for (int i = 0; i < MAX_THREADS_P; i++)
    {
        pthread_join(this->workers[i], NULL);
    }
}

void* RayTracer::render_worker_dummy(void * ptr)
{
    qDebug() << "RayTracer: Worker Thread Started";
    /* this is the nasty work around for pthreads lack of support object contexts */
    (static_cast<RayTracer*>(ptr))->render_worker();
    pthread_exit(NULL);
    return 0;
}

void RayTracer::render_worker()
{
    /*
     * Each worker operates on a different portion of the image dta, so no thread control 
     * mechanism to ensure mutual exclusion is needed.  
     */

    QVector3D colour;
    // TODO: CAMERA CONTROLS
    //Look from the 
    Ray* ray = new Ray(QVector3D(40,10,40), (-QVector3D(40,10,40)).normalized());
    //Ray* ray = new Ray(QVector3D(0,5,15.95), QVector3D(0,-0.2,-1).normalized());
    CastResult* cr = new CastResult();
    unsigned char* ptr;

    uint x, y;
    uint pix;
    //We want to run as a worker until either the cancel flag is set, or the image
    //has been entirely populated. 
    while (!(this->dirtyFlags & FLAG_EXIT))
    {

        //Instantiation of the lock with this constructor will lock the mutex. 
        pthread_mutex_lock(&(this->workTokensMux));
        while(this->workTokens <= 0) pthread_cond_wait(&(this->workTokensCond), &(this->workTokensMux));
        this->workTokens--;
        pthread_mutex_unlock(&(this->workTokensMux));
        //qDebug() << "RayTracer.render_worker: Iteration Started.";

        while (this->nextPixel < (this->_height * this->_width))
        {   
            pix = ++(this->nextPixel); //Maybe i'm over thinking how the volatile keyword works.
            pix -= 1;

            x = pix % this->_width;
            y = (int)(pix / this->_width);
            ptr = this->renderData + (this->renderBPL*y) + (x*4);
            //qDebug() << "RayTracer.render_worker: Assigned Pixel: (" << x << ", " << y << ")";

            cr->reset();
            colour = getPixel(ray, cr, x, y);
            *(ptr++) = std::max(0.0, std::min(colour.z() * 255, 255.0));
            *(ptr++) = std::max(0.0, std::min(colour.y() * 255, 255.0));
            *(ptr++) = std::max(0.0, std::min(colour.x() * 255, 255.0));
            *(ptr++) = ~0;

        }

        qDebug() << "RayTracer.render_worker: Worker complete.";
        //Inidicate that we have finished and return to await another signal to
        //start processing.
        pthread_mutex_lock(&(this->workTokensMux));
        this->workTokens--;
        pthread_mutex_unlock(&(this->workTokensMux));
        //There is a chance that other threads have been created but the 
        //number of workers has been reduced, they are still waiting on
        //conditional variable, so we notify all to ensure we do awaken
        //the master thread.
        pthread_cond_broadcast(&(this->workTokensCond));

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
    //qDebug() << "RayTracer.getPixel: Start";
    QVector3D result;


    //qDebug() << "RayTracer.getPixel: Ray set, firing from (" << x << "," << y << "), from " << ray->origin << " @ " << ray->direction;
    for(int i = 0; i < this->sampleResolution; i++)
    {
        for(int j = 0; j < this->sampleResolution; j++)
        {
            x = x + ((i+this->jitterValues[i+j])/this->sampleResolution);
            y = y + ((j+this->jitterValues[i+j])/this->sampleResolution);
            ray->setToPerspectiveRay(2, renderWidth, renderHeight, x, y);
            //ray->setToOrthographicRay(20.0, renderWidth, renderHeight, x, y);
            cr->reset();

            if(this->sceneManager->cast_ray_into_scene(ray, cr))
            {
                //qDebug() << "RayTracer: Hit!";
                //If we have hit something that is ahead of our vision plane, use
                //the currently shader model to determine pixel colour.
                result += this->activeShader->getPixelColour(cr, this->sceneManager);
                //result += cr->subjectProperties->diffusionCoef;
            }
            else
            {
                //qDebug() << "RayTracer: Miss!";
                //We didn't hit anything in the scene! Use a background colour
                //of hot pink/magenta to indicate this, making it obvious.
                result += QVector3D(0.3,0.3,0.3);
            }
        }
    }

    result /= this->sampleResolution * this->sampleResolution; //Total number of samples, easy opti.

    //qDebug() << "Shader Result: " << result << " for (" << x << "," << y << ")";
    return result;
}


/*
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
*/


