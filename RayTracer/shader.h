/**
 * shader.h
 * A shader model provides interfaces to determine the colour
 * of a pixel. 
 *
 */

#ifndef SHADER_H
#define SHADER_H

#include <QVector3D>
#include "scenemanager.h"
#include "sceneobjectprops.h"
#include "lightsource.h"
#include "ray.h"

class Shader
{
public:
	virtual QVector3D getPixelColour(CastResult* cast, SceneManager* scene) = 0;
};


#endif	
