#include "sphere.h"

#define EPSILON 0.0001f

Sphere::Sphere()
{

}

double Sphere::intersects(Ray ray, QMatrix4x4 transform)
{
	//Default sphere is at 0,0,0 with radius 1.
	QVector3D origin(0,0,0);
	QVector3D aPoint(0,1,0); //A point on the top of the sphere. 
	origin = transform * origin;
	aPoint = transform * aPoint;

	double radius = (aPoint - origin).length();
	QVector3D pmc = ray.origin - origin;

	double A = QVector3D::dotProduct(ray.direction, ray.direction);
	double B = QVector3D::dotProduct(ray.direction, pmc);
	double C = QVector3D::dotProduct(pmc, pmc) - (radius * radius);
	double d = (B * B) - (A * C);

	if(d < EPSILON)
	{
		//the discriminant is close enough to 0
		return -1;
	}

	double sq = sqrt(d);

	double t1 = (-B + sq) / A;
	double t2 = (-B - sq) / A;
	if(t1 <= t2)
	{
		return t1;
	}
	else 
	{
		return t2;
	}
}

QVector3D Sphere::getNormal(QVector3D p, QMatrix4x4 transform)
{
	QVector3D origin(0,0,0);
	origin = transform * origin;

	double radius = (p - origin).length();
	return (p - origin) / radius;
}
