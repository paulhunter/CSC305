/**
 * sceneobjectprops.h
 * SceneObjectProperties encapsulate the physical properties of an object which
 * are then used to determine how light behaves on the surface of that object. 
 * Lights are also encapsulated into these properties through the use of the 
 * emission field. 
 */

#ifndef SCENEOBJECTPROPS_H
#define SCENEOBJECTPROPS_H

#include <QVector3D>

class SceneObjectProperties
{
public:
    SceneObjectProperties();

	/* Create a light source */
	SceneObjectProperties(
		QVector3D emission);
	
	/* Create a material */
	SceneObjectProperties(
		QVector3D ambientCoef,
		QVector3D diffusionCeof,
        QVector3D specularCoef,
        double shininess);

    QVector3D emission; //Light Source colou.
	QVector3D ambientCoef; //Ambient Surface Colour
	QVector3D diffusionCoef; //Surface Colour
	QVector3D specularCoef;//Reflectance Colour
	double shininess; //Specular power 0-128

};


#endif


