/**
 * scenemanager.h
 * The Scene Manager is used to construct and interact with a scene. It contains
 * the scene graph and list of light sources. 
 */

 #ifndef SCENEMANAGER_H
 #define SCENEMANAGER_H

#include <vector>
#include <scenegraphnode.h>
#include <lightsource.h>

class SceneManager
{
public:
	SceneManager();

	SceneGraphNode *root;
	std::vector<LightSource> lights;


};


 #endif
