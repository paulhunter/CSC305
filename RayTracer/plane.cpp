
#ifndef EPSILON
#define EPSILON 0.00001f

#include "plane.h"
#include "sceneobject.h"

Plane::Plane()
{

}

double Plane::intersects(Ray *ray, QMatrix4x4 transform)
{
	/**
	 * We use the formulas available from Shirley pg 78
	 * in which the plane is defined by three points of
	 * a triangle. 
	 * This is simply for expedience in completing the 
	 * assignment now, many optimizations may be made 
	 * this at a later time. 
     *
     * Later I moved to this method below found at the following:
     * http://stackoverflow.com/questions/14972490/ray-tracer-in-c-ray-plane-intersection
	 */

	 //Base plase is on the ground, and is a metre square,
	 //centered on the origin.
     QVector3D n = transform * QVector3D(0.0, 1, 0);
     QVector3D o = transform * QVector3D(0, 0, 0);
     n = (n-o).normalized();

     double t = QVector3D::dotProduct((o-ray->origin),n)/QVector3D::dotProduct(ray->direction,n);

     if (t < 0)
	 {
        t = -1;
	 } 

    return t;
}

QVector3D Plane::getNormal(QVector3D p, QMatrix4x4 transform)
{
    QVector3D n = transform * QVector3D(0.0, 1, 0);
    QVector3D o = transform * QVector3D(0, 0, 0);
    n = (n-o).normalized();
    return n;
}

#endif
