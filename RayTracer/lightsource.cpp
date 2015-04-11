#include "lightsource.h"

LightSource::LightSource(SceneGraphNode * source, double intensity, double ambientIntensity)
{
    this->source = source;
    this->intensity = intensity;
    this->ambientIntensity = ambientIntensity;
}

SceneObject * LightSource::getObject()
{
    return this->source->getSceneObject();
}

SceneObjectProperties * LightSource::getLightProperties()
{
    return this->source->getMaterial();
}

QVector3D LightSource::getLightVector(QVector3D surfacePoint)
{
    //Find the center of the light source geometry.
    //All object primitives have their geometric center on the 
    //origin in the basic model.
    QVector3D lightCenter(0,0,0); 
    lightCenter = this->source->localTransform * lightCenter;
    return (lightCenter - surfacePoint).normalized();
}

/* Maybe later.
LightSource::LightSource(QVector3D colour, QVector3D position, double intensity, double ambientIntensity)
{
    this->colour = colour;
    this->position = position;
    this->intensity = intensity;
    this->ambientIntensity = intensity;
}
*/
