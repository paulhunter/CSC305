/**
 * raytracer.h
 * This raytracer class allows for the creation of an image of a scene. This output
 * is a QtImage which can then be shown on screen/saved to disk. For the moment, its
 * not very interactive and is the logic which creates a sample sphere scene and 
 * renders it.
 */

#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <time.h>
#include <thread>

#include <ray.h>
#include "shader.h"
#include "lambertshader.h"

#include "lightsource.h"
#include "utils.h"
#include <scenemanager.h>
#include <QImage>

class RayTracer
{
public:
	RayTracer();
	QImage render(int width, int height);
	SceneManager *sceneManager;

	Shader* activeShader;

	/* Manually set the thread count of the render process. 
	 * Caution, adding threads past the number of available logical
	 * processors, which is often 8 on most systems these days, will
	 * impeed speed, as additional overhead is added for each thread
	 * waiting to get time on the clock. */
	void setThreadCount(int n);

private:
	volatile int renderCores;

	//A helper to indexing on a row column basis. 
	void setPixel(uint x, uint y, char r, char g, char b, unsigned char* imageData);

	//Render Details
	int renderWidth, renderHeight;
	uint renderBPL; //Bytes per line. 
	volatile bool cancelRender;
	volatile uint nextPixel;
	unsigned char* renderData;


	//TEMPORARY
	double cameraFocalLength;
	LightSource* sceneLight;

	struct renderWork_t {
		uint x,
		uint y, 
		uint width, 
		uint height, 
		uint bpl, 
		unsigned char* imageData
	};
};

#endif
