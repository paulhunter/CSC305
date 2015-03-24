#include "sceneobjectprops.h"

SceneObjectProperties::SceneObjectProperties()
{
    colour = QVector3D(0.7, 0.7, 0.7);
	shine = 100;
	specularCoef = QVector3D(0.5, 0.5, 0.5);
	ambientColour = QVector3D(0.3,0.3,0.3);
	refractiveIndex = 0;
	mirror = 1;
}

SceneObjectProperties::SceneObjectProperties(
		QVector3D colour, 
		double shine,
        QVector3D specularCoef,
		QVector3D ambientColour,
		double refractiveIndex,
		double mirror)
{
	this->colour = colour;
	this->shine = shine;
	this->specularCoef = specularCoef;
	this->ambientColour = ambientColour;
	this->refractiveIndex = refractiveIndex;
	this->mirror = mirror;	
}
