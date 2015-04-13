#include "scenegraphnode.h"
#include <QDebug>

#ifndef EPSILON
#define EPSILON 0.000001f
#endif

SceneGraphNode::SceneGraphNode(SceneObject *object, SceneObjectProperties *material)
{
    this->sceneObject = object;
    this->sceneObjectProperties = material;
}

SceneObject* SceneGraphNode::getSceneObject()
{
	return this->sceneObject;
}

SceneObjectProperties* SceneGraphNode::getSceneObjectProperties()
{
    return this->sceneObjectProperties;
}

bool SceneGraphNode::castRay(Ray *ray, QMatrix4x4 transform, CastResult *result)
{
    double r = -1;
    qDebug() << "HERE";

    if(this->sceneObject == NULL)
    {
        qDebug() << "SceneGraphNode: Root : Cast Ray";
    }
    else
    {
        transform = this->sceneObject->localTransform * transform;
        r = this->sceneObject->intersects(ray, transform);
        if(r > 0 &&
            (result->t < 0 || r < result->t))
        {
            result->subject = this->sceneObject;
            result->subjectProperties = this->sceneObjectProperties;
            result->t = r;
            result->surfacePoint = ray->origin + r*ray->direction;
            result->surfaceNormal = this->sceneObject->getNormal(result->surfacePoint, transform);
            //As we discussed in class, the 'Black Plague' occurs when points on a surface are
            //calculated and as a result of precision errors it ends up calculated as behind
            //the surface. The solution is to move 0.1mm off the surface using the normal vector. 
            result->surfacePoint += EPSILON * result->surfaceNormal;
        }
    }

    //Query all children, who will in turn update the cast result as needed.
    for (std::vector<SceneGraphNode*>::iterator i = children.begin(); i != children.end(); i++)
    {
        (*i)->castRay(ray, transform, result);
    }

    if(result->t >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
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
