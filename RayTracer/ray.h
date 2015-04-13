/**
 * ray.h 
 * A parametric line construct and encapsulated factory methods used by
 * the RayTracer to generate an image. 
 *
 */

 #ifndef RAY_H
 #define RAY_H

#include <QVector3D>

class Ray
{
public:
	/** Slim-Constructor
	 * Used for shadows. No pre-calculation for axes, use set(...) to
	 * set the origin and direction, you need not normalize direction before hand. 
	 */
	Ray();

	/** set
	 * Allows the setting of the origin and direction of the ray manually
	 */
	void set(QVector3D origin, QVector3D direction);

	/** Constructor
	 * Construct the ray base assuming a Y-axis up vector. Use this for calculating
	 * rays for the camera. 
	 */
	Ray(QVector3D eyePos, QVector3D direction);

	/** setToOrthographicRay
	 * Given the focal length of the camera, screen height/width and the pixel indices,
	 * set the structure to the appropriate ray from the center of that pixel. 
	 */
	void setToOrthographicRay(
		double focalLength, 
		double screenWidth, 
		double screenHeight, 
		double i, 
		double j);

	/** setToPerspectiveRay
	 * Given the focal length of the camera, screen height/width and the pixel indicies, 
	 * set the structure to the appropriate ray through the centre of that pixel. 
	 */
	void setToPerspectiveRay(
		double focalLength,
		double screenWidth, 
		double screenHeight, 
		double i, 
		double j);

	/** getPoint
	 * Get a specific point along the parametric line underlying the ray.
	 */
	QVector3D getPoint(double t);

	QVector3D eyePos;
	QVector3D gazeDirection;
	/** origin of the ray */
	QVector3D origin;
	/* direction from origin of the array */
	QVector3D direction;
	/* camera coodinate system */
	QVector3D u;
	QVector3D v;
	QVector3D w;

};

 #endif
