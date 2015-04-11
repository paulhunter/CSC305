/**
 * shader.h
 * A shader model provides interfaces to determine the colour
 * of a pixel. 
 *
 */

#ifndef SHADER_H
#define SHADER_H

#include <QVector3D>
#include "sceneobjectprops.h"
#include "lightsource.h"

class Shader
{
public:
	Shader();

	virtual QVector3D getPixelColour(CastResult* cast, SceneManager* sceneMan) = 0;

	/* Given a rays cast to a point, find the amount of ambient light on the 
	 * surface.
	 */
	QVector3D getAmbientLighting(CastResult* cast, SceneManager* scene);

	/* Given a ray's cast to a point and the scene, find the light intensity
	 * at the surface point, this includes checking for shadows. 
	 */
	QVector3D getSurfaceLighting(CastResult* cast, SceneManager* scene);
};



#endif	
