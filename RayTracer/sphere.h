/** 
 * sphere.h 
 * A primitive representing a sphere and providing means of
 * finding the intersection of a ray with it. 
 */

 #ifndef SPHERE_H
 #define SPHERE_H

 #include <QVector3D>
 #include <QMatrix4x4>
 #include <math.h>
 #include <ray.h>
 #include <sceneobject.h>

class Sphere
{
public:
	/** 
	 *
	 */
	Sphere();
	
	/**
	 * given a ray, find the intersection with the sphere.
	 * Provide a transform to convert the sphere's model coordinates to the camera coordinate. 
	 * Returns the point on the sphere if hit, otherwise, the origin of the ray. 
	 */
	QVector3D intersects(Ray ray, QMatrix4x4 transform);
	
	/**
	 * get the normal vector from a point on the shell of the sphere. 
	 */
	QVector3D getNormal(QVector3D p, QMatrix4x4 transform);

};

 #endif 