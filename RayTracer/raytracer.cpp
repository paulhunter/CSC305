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
    cancelRender = false;
    renderCores = getNumCores();
    qDebug() << "RayTracer: System reporting " << renderCores << " cores online.";

}

void 

QImage RayTracer::render_launch(int width, int height)
{
    this->renderWidth = width;
    this->renderHeight = height;
    unsigned char * image_data = new unsigned char[width * height * 4] //Using RGBA, we need to account for the alpha channel.

}


QImage RayTracer::render_worker(int x, int width, int y, int height, int bpl, unsigned char* imageData)
{
    /*
     * Each worker operates on a different portion of the image dta, so not thread safing 
     * is required. 
     */
    QVector3D colour;
    // TODO: CAMERA CONTROLS
    Ray* ray = new Ray(QVector3D(0,0,800), QVector3D(0,0,-1))
    CastResult cr = new CastResult()
    unsigned char* ptr;
    int sol = x;
    int i, j;
    /* TODO: There are various improvements that cna be made ot the code below */
    for (j = 0; j < height; j++, sol += bpl)
    {
        ptr = imageData + sol;
        for (i = 0; i < width; i++)
        {
            colour = getPixel(ray, cr, x+i, y+j);
            *(p++) = max(0, min(colour.x() * 255, 255));
            *(p++) = max(0, min(colour.y() * 255, 255));
            *(p++) = max(0, min(colour.z() * 255, 255));
            *(p++) = ~0;
        }   
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


