/**
 * raytracer.h
 * This raytracer class allows for the creation of an image of a scene. This output
 * is a QtImage which can then be shown on screen/saved to disk. For the moment, its
 * not very interactive and is the logic which creates a sample sphere scene and 
 * renders it.
 */

#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <ray.h>
#include "shader.h"
#include "lambertshader.h"

#include "lightsource.h"

#include <scenemanager.h>
#include <QImage>

class RayTracer
{
public:
	RayTracer();
	QImage render(int width, int height);
	SceneManager *sceneManager;

	Shader* activeShader;
};

#endif
