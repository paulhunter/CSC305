#include "lambertshader.h"

LambertShader::LambertShader()
{

}

QVector3D lam_getPixelColour(Ray* ray, CastResult* cast, SceneManager* scene, int level)
{
    //qDebug() << "Lambert Shader Start";
    QVector3D eye = ray->origin;
    QVector3D n = cast->surfaceNormal;
    QVector3D sp = cast->surfacePoint;
    SceneObjectProperties* material = cast->subjectProperties;
	/* Ambient Component - Dummy lighting value of 0.005 */
    QVector3D ambient = 0.05 * material->ambientCoef;

    QVector3D diffusion(0,0,0);  //The light coeffecient returned is RGB channeled.
    if(cast->subjectProperties->emission.length() > 0.00001)
    {
        diffusion = cast->subjectProperties->emission;
    }
    else
    {
        /* Diffusion Component */

        for(std::vector<LightSource*>::iterator it = scene->lights.begin(); it != scene->lights.end(); ++it)
        {
            LightSource* light = (*it);
            //If in shadow, do not add its intensity.
            ray->set(sp, light->getLightVector(cast->surfacePoint));
            cast->reset();
            if(scene->cast_ray_into_scene(ray, cast) && cast->subject != light->getObject())
            {
                //We hit something that was not the light. This generally indicates
                //a shadow, but, it can also mean there is a light source in front
                //of the light. In this case, we assume the light absorbs all light
                //hitting it from behind, so it creates an effective shadow.

            }
            else if(cast->subject == light->getObject())
            {
                //Light hits the surface directly.
                diffusion += light->getLightProperties()->emission
                    * fmax(0, QVector3D::dotProduct(cast->surfaceNormal, light->getLightVector(cast->surfacePoint)));
            }
            else
            {
                //We hit nothing int he scene...
            }
        }

        //With the light hitting the surface calcated, muttiply by the surfaces diffusion
        //coeffecient to find out how much of it gets back to the camera.
        diffusion = diffusion * material->diffusionCoef;
    }


    QVector3D color;
	//Add the components together. 
    color = ambient + diffusion;
    if(material->mirrorFactor > 0.1 && level > 0)
    {
        QVector3D mirrorComp;
        ray->set(sp, n);
        cast->reset();
        if( scene->cast_ray_into_scene(ray, cast) )
        {
            mirrorComp = lam_getPixelColour(ray, cast, scene, level-1);
        }
        else
        {
            mirrorComp = color;
        }
        color = (1.0 - material->mirrorFactor) * color + (material->mirrorFactor * mirrorComp);
    }

    //Ensure they are not saturated beyond bounds.
	color.setX(fmin(1, color.x()));
	color.setY(fmin(1, color.y()));
	color.setZ(fmin(1, color.z()));
    //qDebug() << "Lambert Shader Complete";
	return color;
}

QVector3D LambertShader::getPixelColour(Ray* ray, CastResult* cast, SceneManager* scene)
{
    return lam_getPixelColour(ray, cast, scene, 10);
}

