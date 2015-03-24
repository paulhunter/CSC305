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
    virtual double intersects(Ray ray, QMatrix4x4 transform) = 0;
    virtual QVector3D getNormal(QVector3D point, QMatrix4x4 transform) = 0;
};


#endif
