/**
 * sceneobject.h
 * Scene objects are physical entities within the scene This with expand on this
 * base class are primitive shapes such as a sphere, and will support the needed properties.  
 */

#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "ray.h"

class SceneObject 
{
public: 
    SceneObject() {}

	/**
	 * given a ray, find the t-value of the intersection with the sphere.
	 * Returns the t value of the point on the sphere if hit, 
	 * otherwise, the result will be <0;
	 */
    virtual double intersects(Ray ray, QMatrix4x4 transform) = 0;

    /**
	 * get the normal vector from a point object.
	 */
    virtual QVector3D getNormal(QVector3D point, QMatrix4x4 transform) = 0;
};


#endif
