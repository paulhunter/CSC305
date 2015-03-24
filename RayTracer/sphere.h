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

class Sphere : public SceneObject
{
public:
	/** 
	 *
	 */
	Sphere();
	
	/**
	 * given a ray, find the t-value of the intersection with the sphere.
	 * Returns the t value of the point on the sphere if hit, 
	 * otherwise, the result will be <0;
	 */
	double intersects(Ray ray, QMatrix4x4 transform);
	
	/**
	 * get the normal vector from a point on the shell of the sphere. 
	 */
	QVector3D getNormal(QVector3D p, QMatrix4x4 transform);

};

 #endif 