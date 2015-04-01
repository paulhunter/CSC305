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

	for(int i = 0; i < width; i++)
	{
        for(int j = 0; j < height; j++)
		{
            //Reset our results for the next pixel.
            pixelColour.setX(0);
            pixelColour.setY(0);
            pixelColour.setZ(0);
            castresult->reset();

            //ray.setToPerspectiveRay(focalLength, width, height, i, j);
            ray.setToOrthographicRay(focalLength, width, height, i, j);

            if(this->sceneManager->root->castRay(ray, QMatrix4x4(), castresult))
			{
                //If we have hit something that is ahead of our vision plane, use
                //the currently shader model to determine pixel colour.
                pixelColour += this->activeShader->getPixelColour(castresult->surfacePoint,
                    castresult->surfaceNormal, castresult->subject->getMaterial(), light) ;
			}
			else
			{
				//We didn't hit anything in the scene! Use a background colour
                //of dark grey to indicate this.
                pixelColour += QVector3D(0.3,0.3,0.3);
			}
            result.setPixel(i, height - j - 1,
				qRgb(pixelColour.x() * 255, pixelColour.y() * 255, pixelColour.z() * 255));
		}
	}
    qDebug() << "RayTracer: Render completed in " << (std::clock() - start) / CLOCKS_PER_SEC << "seconds.";
	return result;
}


