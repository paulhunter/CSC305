#include "sphere.h"

Sphere::Sphere()
{

}

QVector3D Sphere::intersects(Ray ray, QMatrix4x4 transform)
{

}

QVector3D Sphere::getNormal(QVector3D p, QMatrix4x4 transform)
{
	QVector3D origin(0,0,0);
	origin = transform * origin;

	double radius = (p - origin).length();
	return (p - origin) / radius;
}