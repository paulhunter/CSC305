/**
 * sceneobject.h
 * Scene objects are physical entities within the scene This with expand on this
 * base class are primitive shapes such as a sphere, and will support the needed properties.  
 */

#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

class SceneObject 
{
public: 
	SceneObject();

	virtual double intersects(Ray ray, QMatrix4x4 transform);
	virtual QVector3D getNormal(Ray ray, QMatrix4x4 transform);
};


#endif