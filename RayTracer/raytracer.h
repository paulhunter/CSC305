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
#include <pthread.h>

#include <ray.h>
#include "shader.h"
#include "sceneobject.h"
#include "sceneobjectfactory.h"
#include "materialsfactory.h"
#include "lambertshader.h"

#include "lightsource.h"
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
    /* Resolution change, not screen size */
    void setRenderSize(int width, int height);

    /* Max 16 */
    void setWorkerCount(int count);


	SceneManager *sceneManager;

	Shader* activeShader;

    QImage * image;

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
    pthread_mutex_t managedInterfaceLock;
	// Internals. 

	//Dirty Flags are used to indicate changes in the settings of the render
	//The flags are as follows
	// 0x0001 - Dimension
	// 0x0002 - Camera Position
	// 0x4000 - Worker Count
	// 0x8000 - Exit
	volatile uint dirtyFlags;
	volatile uint nextPixel;
    pthread_t master;
    pthread_t* workers;
    pthread_attr_t workerAttr;
    volatile int workTokens;
    pthread_cond_t workTokensCond;
    pthread_mutex_t workTokensMux;

	
	//Render Frame Data
	unsigned char* renderData;
	volatile uint renderBPL; //Bytes per line.
	//Last rendered image.


	//TEMPORARY
	double cameraFocalLength;

    /* The the active shader and other techniques to calculate the colour
     * of pixel x,y on the screen */
    QVector3D getPixel(Ray* ray, CastResult* cr, int x, int y);

    void render_reconfigure();
    static void* render_master_dummy(void * ptr);
    void render_master();
    static void* render_worker_dummy(void * ptr);
    void render_worker();

};

#endif
