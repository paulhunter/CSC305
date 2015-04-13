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
#include <mutex.h>
#include <condition_variable.hd>

#include <ray.h>
#include "shader.h"
#include "sceneobject.h"
#include "sceneobjectfactory.h"
#include "materialsfactory.h"
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
	// Manipulations to the settings of the render is done through a 
	// a set of pubilc methods which manipulate the variables below. 
	// At the start of each frame render the settings are checked for 
	// changes, at which point these values are copied into the 
	// internals versions which start with an underscore. 
	volatile int renderWidth, renderHeight, renderThreadCount;
	volatile int _width, _height, _workerCount;
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
	std::thread* master;
	std::vector<std::thread *> workers;
	volatile uint workTokens;
	//Conditional Variables requires a Mutex to lock on. 
	std::condition_variable workSema;
	std::mutex workSemaMux;

	
	//Render Frame Data
	unsigned char* renderData;
	volatile uint renderBPL; //Bytes per line.
	//Last rendered image.
	QImage * image;

	//TEMPORARY
	double cameraFocalLength;
};

#endif
