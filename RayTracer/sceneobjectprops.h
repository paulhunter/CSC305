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
		QVector3D colour, 
		double shine,
        QVector3D specularCoef,
		QVector3D ambientColour,
		double refractiveIndex,
		double mirror);

	QVector3D colour;
	double shine;
	QVector3D specularCoef;
	QVector3D ambientColour;
	double refractiveIndex;
	double mirror;
};


#endif


