/**
 * lightsource.h
 * A light source is a standard sphere which can be positioned, and given an
 * intensity and ambient intensity. 
 */

#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <QVector3D>
#include <ray.h>
#include <sphere.h>

class LightSource
{
public:
	LightSource(QVector3D position, double intensity, double ambientIntensity);

	QVector3D getLightDirection(QVector3D destination);
	double intersect(Ray ray);

	QVector3D position;
	double intensity;
	double ambientIntensity;
	SceneObject *source;
};


#endif