/**
 * plane.h	
 * A plane primitive created using a parametric definition
 * 
 */

#ifndef PLANE_H
#define PLANE_H

#include "primitive.h"
#include <math.h>

class Plane : public SceneObject
{
public:
	/** 
	 *
	 */
	Plane();
	
	/**
	 * given a ray, find the t-value of the intersection with the sphere.
	 * Returns the t value of the point on the sphere if hit, 
	 * otherwise, the result will be <0;
	 */
    double intersects(Ray *ray, QMatrix4x4 transform);
	
	/**
	 * get the normal vector from a point on the shell of the sphere. 
	 */
	QVector3D getNormal(QVector3D p, QMatrix4x4 transform);

};


#endif
