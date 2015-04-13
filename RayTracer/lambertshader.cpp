#include "lambertshader.h"

LambertShader::LambertShader()
{

}

QVector3D LambertShader::getPixelColour(CastResult* cast, SceneManager* scene)
{
	/* Ambient Component - Dummy lighting value of 0.3 */
	QVector3D ambient = 0.3 * cast->subjectProperties->ambientCoef;

	/* Diffusion Component */
	QVector3D diffusion(0,0,0);  //The light coeffecient returned is RGB channeled. 
	Ray ray();
	CastResult* cr = new CastResult();
	for(LightSource* light = scene->lights.begin(); light != scene->lights.end(); ++light)
	{
		//If in shadow, do not add its intensity.
		ray.set(cast->surfacePoint, light->getLightVector(cast->surfacePoint));
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
			result += light->intensity * light->getLightProperties()->diffusionCoef 
				* fmax(0, QVector3D::dotProduct(cast->surfaceNormal, light->getLightVector(cast->surfacePoint)));
		}
		else
		{
			//We hit nothing int he scene...
		}
	}

	//With the light hitting the surface calcated, muttiply by the surfaces diffusion
	//coeffecient to find out how much of it gets back to the camera. 
	diffusion = diffusion * cast->subjectProperties->diffusionCoef;

	//Add the components together. 
    color = ambient + diffusion;

    //Ensure they are not saturated beyond bounds. 
	color.setX(fmin(1, color.x()));
	color.setY(fmin(1, color.y()));
	color.setZ(fmin(1, color.z()));

	return color;
}
