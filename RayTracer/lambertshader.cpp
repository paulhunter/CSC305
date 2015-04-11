#include "lambertshader.h"

LambertShader::LambertShader()
{

}

QVector3D LambertShader::getPixelColour(CastResult* cast, SceneManager* sceneMan)
{
	QVector3D color(0,0,0);
	cast->surfacePoint;
	cast->surfaceNormal;
	cast->subject->getMaterial();
	
	QVector3D lightRay = (light->position - surfacePoint).normalized();
    color += material->colour * light->intensity * fmax(QVector3D::dotProduct(lightRay, surfaceNormal), 0);

    //Ensure the colour is not over saturated.

	color.setX(fmin(1, color.x()));
	color.setY(fmin(1, color.y()));
	color.setZ(fmin(1, color.z()));

    //color.normalize();

	return color;
}
