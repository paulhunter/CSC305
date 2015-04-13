/**
 * sceneobjectfactory.h
 * The scene object factory is used to create instances of scene objects 
 * through helpers for transformation. Makes it easy for someone unfamiliar
 * with matrix transformations to get started creating new scenes. 
 * 
 */


#ifndef SCENEOBJECTFACTORY_H
#define SCENEOBJECTFACTORY_H 

#include "sceneobject.h"
#include "sphere.h"
#include "plane.h"
#include "primitivefactory.h"

class SceneObjectFactory;

enum PrimtiveType
{
	SPHERE, /* 1m Radius, Centered on Origin */
	PLANE, /* Default, Laying on XZ Plane */
};

class SceneObjectFactory
{
public: 

	/* Create a basic object at the given position in space. */
	static SceneObject* createSceneObject(PrimitiveType type, QVector3D position);

	/* Create a primitive, scale it by a factor, rotate it about the x, y, z
	 * axes, in that order, finally translating it to the position */
	static SceneObject* createSceneObject_wRot(PrimitiveType type, QVector3D position, double scale, double x, double y, double z);

private:

	/* Retrieve the single instance of a given primive from memory */
	static Primitive * getPrimtive(PrimtiveType type)
	{
		//ASSERT: Could check it, if you really wanted.
		return primtives[type];
	}

	/* Allocated at .... runtime? Compile time? */
	static Primtive * primitives[] = {
		new Sphere(),
		new Plane()
	};

};


#endif