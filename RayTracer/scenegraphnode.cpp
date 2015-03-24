#include "scenegraphnode.h"

SceneGraphNode::SceneGraphNode(SceneObject *object, SceneObjectProperties *material)
{

}

SceneObject* SceneGraphNode::getSceneObject()
{
	return this->sceneObject;
}

SceneObjectProperties* SceneGraphNode::getMaterial()
{
	return this->material;
}

bool SceneGraphNode::castRay(Ray ray, QMatrix4x4 transform, RayImpact *result)
{
	
}

void SceneGraphNode::addChild(SceneGraphNode *child)
{
	if(child != NULL) 
	{
		child->parent = this;
		children.push_back(child);
	}
}

void SceneGraphNode::destroyChildren()
{
	for (std::vector<SceneGraphNode*>::iterator i = children.begin(); i != child.end())
	{
		(*i)->destroyChildren();
		delete (*i);
	}
	children.clear();
}