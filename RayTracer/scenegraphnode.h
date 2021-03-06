/** 
 * scenegraphnode.h
 * A SceneGraphNode is the heart of the scene construct. It contains a reference
 * to the local transform of the node as well as its object if non-root, and its
 * material properties. 
 */

#ifndef SCENEGRAPHNODE_H
#define SCENEGRAPHNODE_H

#include <QMatrix4x4>
#include <sceneobject.h>
#include <sceneobjectprops.h>
#include <ray.h>
#include <castresult.h>

class CastResult;

class SceneGraphNode
{
public:
	SceneGraphNode(SceneObject *obj, SceneObjectProperties *material);

	/** Retrieve the primitive */
	SceneObject *getSceneObject();

	/** Retrieve the material of the primitive */
    SceneObjectProperties * getSceneObjectProperties();

	std::vector<SceneGraphNode*> children;

    /** cast a given ray providing its basis matrix, return true if intersections occurs,
     *  in which case use the resulting CastResult information to determine shading, etc.
     * 
     * Note, the t value test for True, is >= 0. 
     */
    bool castRay(Ray *ray, QMatrix4x4 transform, CastResult *result);

	/** Add a child to this node */
	void addChild(SceneGraphNode *child);

	/** Remove and destroy all children of the node */
	void destroyChildren();

private:
	/** A reference to the parent of this node */
	SceneGraphNode *parent;

	SceneObject *sceneObject;

    SceneObjectProperties *sceneObjectProperties;
};

#endif

