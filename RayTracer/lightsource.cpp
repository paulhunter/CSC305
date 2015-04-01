#include "lightsource.h"

LightSource::LightSource()
{
    this->position = QVector3D(-200,200,200);
	this->intensity = 1.0;
	this->ambientIntensity = 0.5;
}

LightSource::LightSource(QVector3D position, double intensity, double ambientIntensity)
{
	this->position = position;
	this->intensity = intensity;
	this->ambientIntensity = ambientIntensity;
}
