#include "sceneobjectprops.h"

SceneObjectProperties::SceneObjectProperties()
{
    this->diffusionCeof = QVector3D(0.75, 0.75, 0.75);
    this->specularCoef = QVector3D(0,0,0);
    this->light = false;
}

SceneObjectProperties::SceneObjectProperties(
		QVector3D diffusionCeof
        QVector3D specularCoef)
{
	this->diffusionCeof = diffusionCeof;
	this->specularCoef = specularCoef;
	this->light = false;
}
