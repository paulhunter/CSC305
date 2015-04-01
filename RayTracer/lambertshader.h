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

	QVector3D getPixelColour(QVector3D surfacePoint, QVector3D surfaceNormal, SceneObjectProperties* material, LightSource* light);
};


#endif