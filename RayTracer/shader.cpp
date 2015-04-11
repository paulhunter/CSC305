#include "shader.h"

Shader::Shader()
{
	
}

QVector3D getAmbientLighting(CastResult* cast, SceneManager* scene)
{
	/* Calculate the ambient lighting ont he pixel, fuzzy shadows or something? */
	return 0.3; //Dummy stub for the moment, til I know the math. 
}

QVector3D getSurfaceLighting(CastResult* cast, SceneManager* scene)
{
	/* We need to iterate over all the lights and sum those which are not
	 * blocked by another object in the scene. */
	QVector3D result(0,0,0);  //The light coeffecient returned is RGB channeled. 
	Ray ray();
	CastResult* cr = new CastResult();
	for(LightSource* light = scene->lights.begin(); light != scene->lights.end(); ++light)
	{
		//If in shadow, do not add its intensity.
		ray.set(cast->surfacePoint, light->getLightVector());
		cr->reset();
		if(scene->cast_ray_into_scene(ray, cr) && cr->subject != light->getObject())
		{
			//We hit something that was not the light. This generally indicates 
			//a shadow, but, it can also mean there is a light source in front
			//of the light. In this case, we assume the light absorbs all light 
			//hitting it from behind, so it creates an effective shadow. 
		}
		else if(cr->subject == light->getObject())
		{
			//Light hits the surface directly.
			result += light->intensity * light->getLightProperties()->colour;
		}
		else
		{
			//We hit nothing int he scene...
		}
	}

	return result;


}