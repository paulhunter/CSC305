#include "sceneobjectfactory.h"

SceneObjectFactory::SceneObjectFactory()
{
    this->primitives = (PrimitiveShape**)calloc(2, sizeof(PrimitiveShape*));
    this->primitives[PrimitiveShape::SPHERE] = (PrimitiveShape*)(new Sphere());
    this->primitives[PrimitiveShape::PLANE] = (PrimitiveShape*)(new Plane());
}

SceneObject* SceneObjectFactory::createSceneObject(PrimitiveShape::PrimtiveShapeType type, QVector3D position)
{
	SceneObject* result = new SceneObject();
    result->primitive = this->getPrimitive(type);
    result->localTransform.translate(position);
	return result;
}

SceneObject* SceneObjectFactory::createSceneObject_wScaleRot(PrimitiveShape::PrimtiveShapeType type,
	QVector3D position, double scale, double x, double y, double z)
{
	SceneObject* result = new SceneObject();
    result->primitive = this->getPrimitive(type);
    result->localTransform.scale(scale);
    result->localTransform.rotate(x, 1,0,0);
    result->localTransform.rotate(y, 0,1,0);
    result->localTransform.rotate(z, 0,0,1);
    result->localTransform.translate(position);
    return result;
}

SceneObject* SceneObjectFactory::createSceneObject_wScale(PrimitiveShape::PrimtiveShapeType type,
	QVector3D position, double scale)
{
	SceneObject* result = new SceneObject();
    result->primitive = this->getPrimitive(type);
    result->localTransform.scale(scale);
    result->localTransform.translate(position);
    return result;
}

SceneObject* SceneObjectFactory::createSceneObject_wRot(PrimitiveShape::PrimtiveShapeType type,
	QVector3D position, double x, double y, double z)
{
	SceneObject* result = new SceneObject();
    result->primitive = this->getPrimitive(type);
    result->localTransform.rotate(x, 1,0,0);
    result->localTransform.rotate(y, 0,1,0);
    result->localTransform.rotate(z, 0,0,1);
    result->localTransform.translate(position);
    return result;
}

PrimitiveShape* SceneObjectFactory::getPrimitive(PrimitiveShape::PrimtiveShapeType type)
{
    //ASSERT: Could check it, if you really wanted.
    return this->primitives[type];
}
