/**
 * primitive.h
 * Primitives are simple geometry
 */

#ifndef PRIMITIVE_H
#define PRIMITIVE_H

class Primtive
{
	Primtive() {}
	/**
	 * given a ray, find the t-value of the intersection within the geometry.
	 * Returns the t value of the point on the geometry if it hits, 
	 * otherwise, the result will be <0; 
	 */
	virtual double intersects(Ray ray, QMatrix4x4 transform) = 0;

	/**
	 * get the normal vector from the point on the surface.
	 */
	virtual QVector3D getNormal(QVector3D point, QMatrix4x4 transform) = 0;

};

#endif
