
#include "sceneobject.h"

SceneObject::SceneObject()
{

}

/* See primitive.h */
double SceneObject::intersects(Ray *ray, QMatrix4x4 transform)
{
    return SceneObjectFactory::getInstance().getPrimitive(this->type)->intersects(ray, transform);
}

/* See primitive.h */
QVector3D SceneObject::getNormal(QVector3D p, QMatrix4x4 transform)
{
    return SceneObjectFactory::getInstance().getPrimitive(this->type)->getNormal(p, transform);
}
