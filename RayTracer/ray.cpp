#include "ray.h"

Ray::Ray(QVector3D eyePos, QVector3D direction)
{
	this->eyePos = eyePos;
	this->gazeDirection = direction;
	//Grab the Y-axis as the up vector.
	QVector3D up = QVector3D(0,1,0);

	this->w = (-gazeDirection).normalized();
	this->u = QVector3D::crossProduct(up, w).normalized();
	this->v = QVector3D::crossProduct(w,u);
}

void Ray::setToOrthographicRay(double focalLength, double screenWidth, double screenHeight, 
		double i, double j)
{
	double r = screenWidth/2.0;
	double l = -r;
	double t = screenHeight/2.0;
	double b = -t;
	double midu = l + (r - l) * (i + 0.5) / screenWidth;
	double midv = b + (t - b) * (j + 0.5) / screen Height;
	this->origin = this->eyePos + (midu * u) + (midv * v);
	this->direction = -w * focalLength
}

void Ray::setToPerspectiveRay(double focalLength, double screenWidth, double screenHeight, 
		double i, double j)
{
	double r = screenWidth/2.0;
	double l = -r;
	double t = screenHeight/2.0;
	double b = -t;
	double midu = l + (r - l) * (i + 0.5) / screenWidth;
	double midv = b + (t - b) * (j + 0.5) / screen Height;
	this->origin = this->eyePos;
	this->direction = (focalLength * -w) + (midu * u) + (midv * v);
}

QVector3D Ray::getPoint(double t)
{
	return origin + (direction * t)
}