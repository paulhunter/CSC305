/**
 * sceneobjectprops.h
 * SceneObjectProperties encapsulate the physical properties of an object which
 * are then used to determine how light behaves on the surface of that object. 
 */

#ifndef SCENEOBJECTPROPS_H
#define SCENEOBJECTPROPS_H

#include <QVector3D>

class SceneObjectProperties
{
public:
	SceneObjectProperties();
	
	SceneObjectProperties(
		QVector3D diffusionCeof
        QVector3D specularCoef);

	void setIsLight(bool light)
	{
		this->light = light;
	}

	/* The object is a lightsource */
	bool light;
	QVector3D diffusionCoef; //Surface Colour
	QVector3D specularCoef;//Reflectance
};


#endif


