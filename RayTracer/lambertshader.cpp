#include "lambertshader.h"

LambertShader::LambertShader()
{

}

QVector3D LambertShader::getPixelColour(CastResult* cast, SceneManager* scene)
{
    qDebug() << "Lambert Shader Start";
    return QVector3D();
	/* Ambient Component - Dummy lighting value of 0.005 */
    QVector3D ambient = 0.05 * cast->subjectProperties->ambientCoef;

    QVector3D diffusion(0,0,0);  //The light coeffecient returned is RGB channeled.
    if(cast->subjectProperties->emission.length() > 0.00001)
    {
        diffusion = cast->subjectProperties->emission;
    }
    else
    {
        /* Diffusion Component */

        Ray *ray = new Ray();
        CastResult *cr = new CastResult();
        for(std::vector<LightSource*>::iterator it = scene->lights.begin(); it != scene->lights.end(); ++it)
        {
            LightSource* light = (*it);
            //If in shadow, do not add its intensity.
            ray->set(cast->surfacePoint, light->getLightVector(cast->surfacePoint));
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
                diffusion += light->getLightProperties()->emission
                    * fmax(0, QVector3D::dotProduct(cast->surfaceNormal, light->getLightVector(cast->surfacePoint)));
            }
            else
            {
                //We hit nothing int he scene...
            }
        }

        delete ray;
        delete cr;

        //With the light hitting the surface calcated, muttiply by the surfaces diffusion
        //coeffecient to find out how much of it gets back to the camera.
        diffusion = diffusion * cast->subjectProperties->diffusionCoef;
    }


    QVector3D color;
	//Add the components together. 
    color = ambient + diffusion;

    //Ensure they are not saturated beyond bounds. 
	color.setX(fmin(1, color.x()));
	color.setY(fmin(1, color.y()));
	color.setZ(fmin(1, color.z()));
    //qDebug() << "Lambert Shader Complete";
	return color;
}
