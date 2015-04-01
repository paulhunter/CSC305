#include "lightsource.h"

LightSource::LightSource()
{
    //Default configuration, used for initial rayTracer setup.
    this->colour = QVector3D(0,0,0); //Default to true white light
    this->position = QVector3D(-100,200,500);
	this->intensity = 1.0;
	this->ambientIntensity = 0.5;
}

LightSource::LightSource(QVector3D position, double intensity, double ambientIntensity)
{
	this->position = position;
    this->colour = QVector3D(0,0,0); //Default to a true white light.
	this->intensity = intensity;
	this->ambientIntensity = ambientIntensity;
}

LightSource::LightSource(QVector3D colour, QVector3D position, double intensity, double ambientIntensity)
{
    this->colour = colour;
    this->position = position;
    this->intensity = intensity;
    this->ambientIntensity = intensity;
}
