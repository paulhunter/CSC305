#include "lambertshader.h"

LambertShader::LambertShader()
{

}

QVector3D LambertShader::getPixelColour(QVector3D surfacePoint, QVector3D surfaceNormal, SceneObjectProperties* material, LightSource* light)
{
	QVector3D color(0,0,0);
	QVector3D lightRay = (light->position - surfacePoint).normalized();
	color += material->colour * light->intensity * fmax(QVector3D::dotProduct(lightRay, surfaceNormal), 0);

	//Ensure the colour is not over saturated. 
	color.setX(fmin(1, color.x()));
	color.setY(fmin(1, color.y()));
	color.setZ(fmin(1, color.z()));

	return color;
