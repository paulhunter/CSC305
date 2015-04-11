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

/* Maybe later.
LightSource::LightSource(QVector3D colour, QVector3D position, double intensity, double ambientIntensity)
{
    this->colour = colour;
    this->position = position;
    this->intensity = intensity;
    this->ambientIntensity = intensity;
}
*/
