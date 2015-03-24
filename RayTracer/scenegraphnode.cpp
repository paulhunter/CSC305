#include "scenegraphnode.h"
#include <QDebug>

SceneGraphNode::SceneGraphNode(SceneObject *object, SceneObjectProperties *material)
{
    this->sceneObject = object;
    this->material = material;
}

SceneObject* SceneGraphNode::getSceneObject()
{
	return this->sceneObject;
}

SceneObjectProperties* SceneGraphNode::getMaterial()
{
	return this->material;
}

bool SceneGraphNode::castRay(Ray ray, QMatrix4x4 transform, int *result)
{
    double r;
    transform = localTransform * transform;
    if(this->sceneObject != NULL)
    {
        r = this->sceneObject->intersects(ray, transform);
        if(r > 1)
        {
            return true;
        }
    }

    for (std::vector<SceneGraphNode*>::iterator i = children.begin(); i != children.end(); i++)
    {
        if((*i)->castRay(ray, transform, result))
        {
            return true;
        }
    }
    return false;
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
    for (std::vector<SceneGraphNode*>::iterator i = children.begin(); i != children.end(); i++)
	{
		(*i)->destroyChildren();
		delete (*i);
	}
	children.clear();
}
