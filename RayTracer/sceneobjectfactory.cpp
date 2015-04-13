#include "sceneobjectfactory.h"

SceneObject* SceneObjectFactory::createSceneObjectAtPos(PrimitiveType type, QVector3D position)
{
	SceneObject* result = new SceneObject();
	result->primitive = getPrimitive(type);
	result->transform.translate(position);
	return result;
}

SceneObject* SceneObjectFactory::createSceneObject_wScaleRot(PrimitiveType type, 
	QVector3D position, double scale, double x, double y, double z)
{
	SceneObject* result = new SceneObject();
	result->primitive = getPrimitive(type);
	result->transform.scale(scale);
	result->transform.rotate(x, 1,0,0);
	result->transform.rotate(y, 0,1,0);
	result->transform.rotate(z, 0,0,1);
	result->transform.translate(position);
}

SceneObject* SceneObjectFactory::createSceneObject_wScale(PrimitiveType type, 
	QVector3D position, double scale)
{
	SceneObject* result = new SceneObject();
	result->primitive = getPrimitive(type);
	result->transform.scale(scale);
	result->transform.translate(position);
}

SceneObject* SceneObjectFactory::createSceneObject_wRot(PrimitiveType type, 
	QVector3D position, double x, double y, double z)
{
	SceneObject* result = new SceneObject();
	result->primitive = getPrimitive(type);
	result->transform.rotate(x, 1,0,0);
	result->transform.rotate(y, 0,1,0);
	result->transform.rotate(z, 0,0,1);
	result->transform.translate(position);
}