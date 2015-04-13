#include <scenemanager.h>


SceneManager::SceneManager()
{
	this->root = new SceneGraphNode(NULL, NULL);
}

void SceneManager::add_sceneObject(SceneObject* obj, SceneObjectProperties* material)
{
	this->root->addChild(new SceneGraphNode(obj, material));
}

void SceneManager::add_lightSource(SceneObject* obj, SceneObjectProperties* material)
{
	SceneGraphNode *light = new SceneGraphNode(obj, material);
	this->root->addChild(light);
	this->lights.push_back(new LightSource(light));
}

bool SceneManager::cast_ray_into_scene(Ray ray, CastResult *result)
{
	return this->root->castRay(ray, QMatrix4x4(), result);
}