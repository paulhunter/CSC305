/**
 * sceneobject.h
 * Scene objects are physical entities within the scene. The include a
 * primitive object that defines their geometry, and a transform 
 * providing its location and final shape. 
 */

#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "ray.h"
#include "primitive.h"

class SceneObject 
{
public: 
    SceneObject() {}

    Primitive* primitive;

    /**
     * A local
     */
    QMatrix4x4 localTransform;
};


#endif
