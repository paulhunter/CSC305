/**
 * sceneobjectfactory.h
 * The scene object factory is used to create instances of scene objects 
 * through helpers for transformation. Makes it easy for someone unfamiliar
 * with matrix transformations to get started creating new scenes. 
 * 
 */


#ifndef SCENEOBJECTFACTORY_H
#define SCENEOBJECTFACTORY_H 

#include <QVector3D>
#include "sceneobject.h"
#include "sphere.h"
#include "plane.h"
#include "primitive.h"

class SceneObjectFactory
{
public: 
    SceneObjectFactory();

    static SceneObjectFactory * instance;
    PrimitiveShape ** primitives;

    static SceneObjectFactory& getInstance()
    {
        static SceneObjectFactory instance;
        return instance;
    }

	/* Create a basic object at the given position in space. */
    SceneObject* createSceneObject(PrimitiveShape::PrimtiveShapeType type, QVector3D position);

	/* Create a scaled primitive at the given position in space .*/
    SceneObject* createSceneObject_wScale(PrimitiveShape::PrimtiveShapeType type, QVector3D position, double scale);

	/* Create a rotated primitive with original scale */
    SceneObject* createSceneObject_wRot(PrimitiveShape::PrimtiveShapeType type, QVector3D position, double x, double y, double z);

	/* Create a primitive, scale it by a factor, rotate it about the x, y, z
	 * axes, in that order, finally translating it to the position */
    SceneObject* createSceneObject_wScaleRot(PrimitiveShape::PrimtiveShapeType type, QVector3D position, double scale, double x, double y, double z);

private:

	/* Retrieve the single instance of a given primive from memory */
    PrimitiveShape * getPrimitive(PrimitiveShape::PrimtiveShapeType type);

};


#endif
