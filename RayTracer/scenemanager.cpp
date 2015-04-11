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
	this->add_lightSource(object, material, 0.7, 0.2);
}


void SceneManager::add_lightSource(SceneObject* obj, SceneObjectProperties* material,
	double intensity, double ambientIntensity)
{
	material->setIsLight(true); //Just set it in case they didn't.
	SceneGraphNode *light = new SceneGraphNode(obj, material);
	this->root->addChild(light);
	this->lights.push_back(new LightSource(light, intensity, ambientIntensity));
}

bool SceneManager::cast_ray_into_scene(Ray ray, CastResult *result)
{
	return this->root->castRay(ray, QMatrix4x4(), result);
}