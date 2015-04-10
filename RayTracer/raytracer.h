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
#include <mutex>
#include <condition_variable>

#include <ray.h>
#include "shader.h"
#include "lambertshader.h"

#include "lightsource.h"
#include "utils.h"
#include <scenemanager.h>
#include <QImage>

#define FLAG_DIMENSIONS 0x0001
#define FLAG_WORKER_COUNT 0x2000
#define FLAG_RENDER_ENABLED 0x4000
#define FLAG_EXIT 0x8000

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

	// ///////////////////////////
	// Render Details
	// ///////////////////////////
	//Storage for configuration changes before application. 
	volatile int renderWidth, renderHeight, renderThreadCount;
	std::mutex managedInterfaceLock;
	// Internals. 

	//Dirty Flags are used to indicate changes in the settings of the render
	//The flags are as follows
	// 0x0001 - Dimension
	// 0x0002 - Camera Position
	// 0x4000 - Worker Count
	// 0x8000 - Exit
	volatile uint dirtyFlags;
	volatile uint nextPixel;
	std::vector<std::thread *> workers;
	volatile uint workTokens;
	//Conditional Variables requires a Mutex to lock on. 
	std::condition_variable workSema;
	std::mutex workSemaMux;
	

	

	unsigned char* renderData;
	QImage * image;

	//
	

	uint renderBPL; //Bytes per line. 
	volatile bool cancelRender;

	std::mutex renderMux;


	//TEMPORARY
	double cameraFocalLength;
	LightSource* sceneLight;

};

#endif
