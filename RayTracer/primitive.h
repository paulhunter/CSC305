/**
 * primitive.h
 * Primitives are simple geometry
 */

#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <QMatrix4x4>
#include <QVector3D>
#include "ray.h"

class PrimitiveShape
{
public:

    enum PrimtiveShapeType
    {
        SPHERE = 0, /* 1m Radius, Centered on Origin */
        PLANE = 1 /* Default, Laying on XZ Plane */
    };

	/**
	 * given a ray, find the t-value of the intersection within the geometry.
	 * Returns the t value of the point on the geometry if it hits, 
	 * otherwise, the result will be <0; 
	 */
    virtual double intersects(Ray *ray, QMatrix4x4 transform) = 0;

	/**
	 * get the normal vector from the point on the surface.
	 */
	virtual QVector3D getNormal(QVector3D point, QMatrix4x4 transform) = 0;
};

#endif
