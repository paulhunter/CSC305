/**
 * scenemanager.h
 * The Scene Manager is used to construct and interact with a scene. It contains
 * the scene graph and list of light sources. 
 */

 #ifndef SCENEMANAGER_H
 #define SCENEMANAGER_H

class
{
public:
	SceneManager();

	SceneGraphNode *root;
	std::vector<LightSource> lights;


};


 #endif