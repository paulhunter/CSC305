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
 #include "sceneobject.h"
 #include "ray.h"


class Sphere : public Primtive
{
public:
	/** 
	 *
	 */
	Sphere();
	
	/* See primitive.h */
	double intersects(Ray ray, QMatrix4x4 transform);
	
	/* See primitive.h */
	QVector3D getNormal(QVector3D p, QMatrix4x4 transform);

};

 #endif 
