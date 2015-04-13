/**
 * lightsource.h
 * A light source is a standard sphere which can be positioned, and given an
 * intensity and ambient intensity. 
 */

#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <QVector3D>
#include "ray.h"
#include "sphere.h"

class LightSource
{
public:
	/** A 'standard' white light source at 0,10,0; */
	LightSource(SceneGraphNode * source);
    
    /* Perhaps later add this back wrapping a simple sphere/point source */
    //LightSource(QVector3D colour, QVector3D position, double intensity, double ambientIntensity);

	/* Calculate the unit vector of the ray from the surface point to
	 * the light source */
	QVector3D getLightVector(QVector3D surfacePoint);

	SceneObject *getObject();
	SceneObjectProperties *getLightProperties();
private:
    SceneGraphNode * source;
};


#endif
