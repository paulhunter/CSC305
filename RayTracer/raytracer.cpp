#include <raytracer.h>
#include <QDebug>

RayTracer::RayTracer()
{
	//Add scene creation.
	this->sceneManager = new SceneManager();
    SceneGraphNode *root = new SceneGraphNode(NULL, NULL);
	this->sceneManager->root = root;

	SceneGraphNode *sphere = new SceneGraphNode(new Sphere(), new SceneObjectProperties());
    sphere->localTransform.scale(20);
	sphere->localTransform.translate(0, 0.5, 0);
	root->addChild(sphere);

	//TODO Allow multiple lights. 
	LightSource * light = new LightSource();

}

QImage RayTracer::render(int width, int height)
{
    //TODO: Incorporate Camera Controls.
    Ray ray(QVector3D(0, 0.5, 100), QVector3D(0,0,-1));

    //TODO: Create RayImpact to be used to find which scene object is closest to the eye
    //RayImpact castResult = RayImpact();
    int castResult;
	QVector3D pixelColour;
    QImage result = QImage(width, height, QImage::Format_RGB32);
	
    double focalLength = 1;

	for(int i = 0; i < width; i++)
	{
        for(int j = 0; j < height; j++)
		{
            pixelColour = QVector3D(0,0,0);


            //ray.setToPerspectiveRay(focalLength, width, height, i, j);
            ray.setToOrthographicRay(focalLength, width, height, i, j);

            //qDebug() << "Casting Ray: " << ray.origin << " in direction " << ray.direction;
            if(this->sceneManager->root->castRay(ray, QMatrix4x4(), &castResult))
			{
				//TODO: Call shader to get pixel colour.
				pixelColour += QVector3D(1.0, 0, 0); //Filler Colour
			}
			else
			{
				//We didn't hit anything in the scene! Use a background colour
				//of harsh purple to indicate this.
                pixelColour += QVector3D(0.1,0.1,0.1);
			}
            result.setPixel(i, height - j - 1,
				qRgb(pixelColour.x() * 255, pixelColour.y() * 255, pixelColour.z() * 255));
		}
	}
	return result;
}


