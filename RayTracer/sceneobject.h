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
#include "sceneobjectfactory.h"

class PrimitiveShape; //Forward Declaration - see primitive.h

class SceneObject 
{
public: 
    SceneObject();

    /* See primitive.h */
    double intersects(Ray *ray, QMatrix4x4 transform);

    /* See primitive.h */
    QVector3D getNormal(QVector3D p, QMatrix4x4 transform);

    PrimitiveShape::PrimtiveShapeType type;

    /**
     * A local
     */
    QMatrix4x4 localTransform;
};


#endif
