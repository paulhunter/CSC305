/**
 * lambertshader.h
 * A shader which uses Lambert's model for shading.
 */

#ifndef LAMBERTSHADER_H
#define LAMBERTSHADER_H

#include "shader.h"

class LambertShader : public Shader
{
public:
	LambertShader();

	/* See shader.h */
	QVector3D getPixelColour(CastResult* cast, SceneManager* scene);
};


#endif