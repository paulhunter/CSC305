#include "ray.h"

Ray::Ray()
{

}

void Ray::set(QVector3D origin, QVector3D direction)
{
	//Default the ray to the eye and direction in case
	//it is being used for shadow calculations. 
	this->origin = origin;
	this->direction = direction.normalized();
}


Ray::Ray(QVector3D eyePos, QVector3D direction)
{
	this->eyePos = eyePos;
	this->gazeDirection = direction.normalized();

	QVector3D up = QVector3D(0,1,0);

	this->w = (-gazeDirection).normalized();
	this->u = QVector3D::crossProduct(up, w).normalized();
	this->v = QVector3D::crossProduct(w,u).normalized();
}

void Ray::setToOrthographicRay(double scale, double screenWidth, double screenHeight, 
		double i, double j)
{
	double midu = ((-screenWidth/2.0) + (i + 0.5)) / screenWidth;
    double midv = ((screenHeight/2.0) - (j - 0.5)) / screenHeight;
	this->origin = this->eyePos + (scale*midu * u) + (scale*midv * v);
    this->direction = -w; //Our direction vector becomes the length of the 
    //hypothetical lens from the sensor.
}

void Ray::setToPerspectiveRay(double focalLength, double screenWidth, double screenHeight, 
		double i, double j)
{
	double midu = ((-screenWidth/2.0) + (i + 0.5)) / screenWidth;
	double midv = ((screenHeight/2.0) - (j - 0.5)) / screenHeight;
	this->origin = this->eyePos + (midu * u) + (midv * v);
    this->direction = ((-w*(0.5*focalLength)) + (midu * u) + (midv * v)).normalized();
	//Hard coded for the moment. 
}

QVector3D Ray::getPoint(double t)
{
    return origin + (direction * t);
}
