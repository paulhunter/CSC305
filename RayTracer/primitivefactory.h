/**
 * primtivefactory.h
 * The Primitive Factory contains an instance of each primitive object. 
 */

#ifndef PRIMITIVEFACTORY_H
#define PRIMITIVEFACTORY_H

#include "primitive.h"
#include "sphere.h"

class PrimitiveFactory
{

	enum PrimitiveType {
		/* Sphere:
		 * Spheres are radius 1m and positioned with their center at the origin.
		 */
		SPHERE
	};

public:
	static Primitive * getPrimtive(PrimtiveType type)
	{
		//ASSERT: Could check it, if you really wanted.
		return primtives[type];
	}

private:
	static Primtive * primitives = {
		new Sphere()
	};
};



#endif