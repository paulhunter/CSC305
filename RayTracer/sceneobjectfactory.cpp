#include "sceneobjectfactory.h"

SceneObjectFactory::SceneObjectFactory()
{

}

SceneObjectFactory* SceneObjectFactory::getInstance()
{
	if (instance == NULL)
	{
		instance = new SceneObjectFactory();
	}
	return instance;
}

SceneObject* SceneObjectFactory::createSceneObjectAtPos(PrimitiveType type, QVector3D position)
{
	SceneObject* result = new SceneObject();
	result->primitive = getPrimitive(type);
	result->transform.translate(position);
	return result;
}