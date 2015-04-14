#include "bpfshader.h"

#define DEPTH_LIMIT 5
#ifndef EPSILON
#define EPSILON 0.00001f
#endif

BlinnPhongReflectiveShader::BlinnPhongReflectiveShader()
{

}



//This helper provides the recursive algorithm needed to make multiple
//reflections eloquent.
//Ray is a pre-allocated and assigned
//CastResults is a valid cntainer in memory which can be made use of
//by the method,
QVector3D bpfs_cast_ray(Ray* ray, CastResult* cr, SceneManager* scene, int level)
{
    /* Memory operations are expensive, so I want to avoid them. The easiest way to do
     * this is mimic the worker threads pattern of allocating and providing helpers
     * with a point to a Ray or CastResult. However, in a shader, I have multiple
     * rays to cast in order to calculate the colour of a pixel whos ray hit the first
     * surface. Rather than create another allocated ray at each level, we save a local
     * pointer to one of the materials in the factory; allowing us to reuse the ray,
     * more or less free of charge */

    QVector3D mirrorComp;
    SceneObjectProperties* material = cr->subjectProperties; //Local copy of material.
    QVector3D v = (cr->surfacePoint-ray->origin).normalized(); //Calculate now before CR is reused.
    QVector3D n = (cr->surfaceNormal).normalized();
    QVector3D sp = (cr->surfacePoint);

    /* Ambient Component - Dummy lighting value of 0.005 */
    QVector3D ambient = 0.05 * cr->subjectProperties->ambientCoef;

    QVector3D diffusion(0,0,0);  //The light coeffecient returned is RGB channeled.
    QVector3D specular(0,0,0);
    if(material->emission.length() > EPSILON)
    {
        diffusion = material->emission;
    }
    else
    {
        /* Diffusion Component */
        for(std::vector<LightSource*>::iterator it = scene->lights.begin(); it != scene->lights.end(); ++it)
        {
            LightSource* light = (*it);
            //If in shadow, do not add its intensity.
            QVector3D l = light->getLightVector(sp);
            ray->set(sp, l);
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
                    * fmax(0, QVector3D::dotProduct(sp, l));
                specular += light->getLightProperties()->emission
                             * pow(fmax(QVector3D::dotProduct((l-v).normalized(), n),0), material->shininess);
            }
            else
            {
                //We hit nothing int he scene...
            }
        }

        //With the light hitting the surface calcated, muttiply by the surfaces diffusion
        //coeffecient to find out how much of it gets back to the camera.
        diffusion = diffusion * material->diffusionCoef;


        //Specular Component.
        specular = specular * material->specularCoef;

    }


    QVector3D color;
    color = (ambient + diffusion + specular);
    //Add Mirror component if present
    if(material->mirrorFactor > EPSILON && level > 0)
    {
        ray->set(sp, n);
        cr->reset();
        if( scene->cast_ray_into_scene(ray, cr) )
        {
            mirrorComp = bpfs_cast_ray(ray, cr, scene, level-1);
        }
        else
        {
            mirrorComp = QVector3D(0.3, 0.3, 0.3);
        }
        color = (1.0 - material->mirrorFactor) * color + (material->mirrorFactor * mirrorComp);
    }



    color.setX(fmin(1, color.x()));
    color.setY(fmin(1, color.y()));
    color.setZ(fmin(1, color.z()));

    return color;
}


QVector3D BlinnPhongReflectiveShader::getPixelColour(Ray* ray, CastResult* cast, SceneManager* scene)
{
    return bpfs_cast_ray(ray, cast, scene, DEPTH_LIMIT);
}

