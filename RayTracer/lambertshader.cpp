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
    QVector3D ambient(0,0,0);

    QVector3D diffusion(0,0,0);  //The light coeffecient returned is RGB channeled.
    QVector3D specular(0,0,0);
    QVector3D halfway;
    if(cast->subjectProperties->emission.length() > 0.00001)
    {
        diffusion = cast->subjectProperties->emission;
    }
    else
    {
  

        for(std::vector<LightSource*>::iterator it = scene->lights.begin(); it != scene->lights.end(); ++it)
        {
            LightSource* light = (*it);
            //If in shadow, do not add its intensity.
            ray->set(sp, light->getLightVector(sp));
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
                    * fmax(0, QVector3D::dotProduct(n, light->getLightVector(sp)));
                halfway = (light->getLightVector(sp) + (eye-sp)).normalized();
                specular += light->getLightProperties()->emission
                    * fmax(0, pow(QVector3D::dotProduct(n, h), material->shininess);
            }
            else
            {
                //We hit nothing int he scene...
            }
        }

        //With the light hitting the surface calcated, muttiply by the surfaces diffusion
        //coeffecient to find out how much of it gets back to the camera.
        ambient    = 0.15 * material->ambientCoef;
        diffusion *= 0.70 * material->diffusionCoef;
        specular  *= 0.15 * material->specularCoef;
    }


    QVector3D color;
	//Add the components together. 
    color = ambient + diffusion; + specular;
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
    if(color.length() > 1.75)
    {
        qDebug() << "ERROR: Shader Colour outside bounds!";
        color(0,0,0);
    }

    //qDebug() << "Lambert Shader Complete";
	return color;
}

QVector3D LambertShader::getPixelColour(Ray* ray, CastResult* cast, SceneManager* scene)
{
    return lam_getPixelColour(ray, cast, scene, 10);
}

