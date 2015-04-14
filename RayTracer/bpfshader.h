#ifndef BLINNPHONGREFLECTIVESHADER_H
#define BLINNPHONGREFLECTIVESHADER_H

#include "lambertshader.h"

class BlinnPhongReflectiveShader : public Shader
{
public:
    BlinnPhongReflectiveShader();
    /* See Shader.h */
    QVector3D getPixelColour(Ray* ray, CastResult* cast, SceneManager* scene);
private:
    LambertShader* ad_helper; //Ambient/Diffusion worker.
};

#endif // BLINNPHONGREFLECTIVESHADER_H
