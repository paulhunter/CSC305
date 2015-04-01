/**
 * shader.h
 * A shader model provides interfaces to determine the colour
 * of a pixel. 
 *
 */

#ifndef SHADER_H
#define SHADER_H

#include <QVector3D>


class Shader
{
public:
	Shader();

	virtual QVector3D getPixelColour(QVector3D surfacePoint, QVector3D surfaceNormal, SceneObjectProperties* material, LightSource* light);
};



#endif	