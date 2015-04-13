/** 
 * sphere.h 
 * A Sphere Primitive. 
 * 1m in radius, center positioned at the origin.
 */

#ifndef SPHERE_H
#define SPHERE_H

#include <QVector3D>
#include <QMatrix4x4>
#include <math.h>
#include "sceneobject.h"
#include "ray.h"
#include "primitive.h"


class Sphere : PrimitiveShape
{
public:
	/** 
	 * Basic Constructor.
	 */
	Sphere();
	
	/* See primitive.h */
	double intersects(Ray ray, QMatrix4x4 transform);
	
	/* See primitive.h */
	QVector3D getNormal(QVector3D p, QMatrix4x4 transform);

};

 #endif 
