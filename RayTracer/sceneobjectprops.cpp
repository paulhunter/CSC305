#include "sceneobjectprops.h"

SceneObjectProperties::SceneObjectProperties()
{
    this->diffusionCoef = QVector3D(0.75, 0.75, 0.75);
    this->specularCoef = QVector3D(0,0,0);
}

SceneObjectProperties::SceneObjectProperties(
	QVector3D emission)
{
	this->emission = emission;
}

SceneObjectProperties::SceneObjectProperties(
		QVector3D ambientCoef,
        QVector3D diffusionCoef,
        QVector3D specularCoef, 
        double shininess)
{
	this->ambientCoef = ambientCoef;
    this->diffusionCoef = diffusionCoef;
	this->specularCoef = specularCoef;
	this->shininess = shininess;
}
