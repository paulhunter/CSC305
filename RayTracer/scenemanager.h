/**
 * scenemanager.h
 * The Scene Manager is used to construct and interact with a scene. It contains
 * the scene graph and list of light sources, and provides an abstraction for 
 * the ray tracer from the data structure that is being used to store the scene. 
 * 
 * As a result, the class contains a method for casing a ray into the scene. 
 * If the ray tracer is to cast a ray, it will call this method, which will in 
 * turn call the datastructure's method as needed. 
 * 
 * Future work will include integrating a better datastructure than the current
 * scene graph to ensure that we are looking up collisions of rays with objects
 * in the scene with a reasonble amount of speed. 
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

	/* Objects */
	/* Add an object to the scene. It should be pre-constructed
	 * with each of its children before it is passed into this 
	 * method to add it to the scene graph. 
	 */
	void add_sceneObject(SceneObject* obj, ObjectMaterial* material);

	/* Lights */
	/* Add a new light source to the scene. It should be pre-
	 * constructed as it should be used. Defsult intensity settings
	 * are applied.
	 *
	 * The scene manager will ensure the destruction of the light
	 * object after use */
	void add_lightSource(SceneObject* obj, ObjectMaterial* material);

	/* Add a new light with a specified intensity. */
	void add_lightSource(SceneObject* obj, ObjectMaterial* material,
		double intensity, double ambientIntensity);

	/* Utilities */
	/* Cast a ray into the scene, returning the results of the
	 * collision in the provided and previously allocated
	 * cast result. 
	 */
	bool cast_ray_into_scene(Ray ray, CastResult *result);

	std::vector<LightSource*> lights;
private:
	
	SceneGraphNode *root;
	


};


 #endif
