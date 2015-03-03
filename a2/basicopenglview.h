/*
 * basicopenglview.h
 *
 * Created by: Brian Wyvill
 * Last Author: Paul Hunter
 *
 * CSC 305 - Assignment 2 - Viewing 3D Objects.
 *
 * BasicOpenGLView is a QWidget that allows to interact
 * with the camera using their mouse. Dollying is done with
 * the mouse wheel, azimuth and elevation can be changed by
 * first pressing the right mouse button and dragging.
 * Horizontal movement will result in azimuth adjustments and
 * Vertical movement will be translated to adjustments
 * in the elevation of the camera.
 *
 */

#ifndef BASICOPENGLVIEW_H
#define BASICOPENGLVIEW_H

#include <stdlib.h>
#include <math.h>
#include <time.h>           //Used for 'random' seed generation.
#include <QGLWidget>
#include <QtDebug>
#include <QVector>          //Dynamic Array
#include <QVector2D>
#include <QVector3D>        //A 3 element structure
#include <QStack>           //Stack implementation used for convenience
#include <QGenericMatrix>   //Generic Matrice Classes
#include <QMatrix>          //Matrix support methods.
#include <QMouseEvent>
#include <QMatrix4x4>

#define V_RADIUS 5 //Vertex radius
#define MAX_CAM_AZI 1.57 //Just shy of full vertical.
#define MIN_CAM_AZI 0.2  //Just off the ground.
#define MAX_CAM_DIS 800.0 //Just a wee spec that cube is.
#define MIN_CAM_DIS 15.0  //Close enough to allow clipping?
#define CAM_FOV 1.57 //90 degrees.

/**
  * @class  BasicOpenGLView
  * @brief  our OpenGL view derived from QGLWidget.
  * Allows for the drawing and transformation of wirepolygons.
  */
class BasicOpenGLView : public QGLWidget
{
    /**
      * macro needed to be inserted in every QT derived class.
      */
    Q_OBJECT
public:

    /**
      * our constructor
      * @param  parent the parent object of the widget.
                pass this one on to the superclass constructor
      */
    explicit BasicOpenGLView(QWidget *parent = 0);

    /**
     * @brief SetCameraPosition allows for manual positioning of the camera, useful
     * for restoring viewpoints.
     * @param azimuth in radians
     * @param elevation in radians in range [0, 1.57].
     * @param distance in radians in range [15, 800]
     */
    void SetCameraPosition(double azimuth, double elevation, double distance);

signals:

public slots:

protected:
    /**
      * function called automatically by QT after the OpenGL context is created
      * in here, do all OpenGL setup stuff, that you can before the actual program
      * execution starts
      */
    void initializeGL();

    /**
      * the function called whenever our Widget is being redrawn.
      * assume that the BasicOpenGLView's OpenGL context has already
      * been made the current one, so no need to call
      * this->makeCurrent(); anymore
      * Do all your rendering loop related code in there
      */
    void paintGL();

    /**
      * method called when the widget is resized.
      * we need code in there, to react to the changed window size
      * otherwise the rendering will look skewed and ugly
      */
    void resizeGL(int width, int height);

    /**
      * function called when a mouse button is pressed and the cursor is hovering
      * over our widget
      * use the QMouseEvent classmembers to access the mouse information
      */
    void mousePressEvent(QMouseEvent *event);

    /**
      * function called when mouse cursor is moved inside our widgets region
      * use the QMouseEvent classmembers to access the mouse information
      */
    void mouseMoveEvent(QMouseEvent *event);

    /**
      * function called when a mouse button is released and the cursor is hovering
      * over our widget
      * use the QMouseEvent classmembers to access the mouse information
      */
    void mouseReleaseEvent(QMouseEvent *event);

    /**
      * function called when the wheel of the mouse is spun.
      */
    void wheelEvent(QWheelEvent * event);

private:
    //Mouse Controls + Polygon Modification
    bool _mouseButtonDown; //Mouse button pressed -> True

    //Cube - A collection of twelve faces, of 12 colours.
    QVector< QVector<QVector4D> > _cube;
    QVector<QVector3D> _cube_panel_colors;
    void initCube(); //Initialization for the triangles forming the cube.

    //Camera Info
    double _cam_azimuth; //Radians from X axis.
    double _cam_elevation; //Radians above XZ plane in range [0, 1.57]
    double _cam_distance;  //Distance from the view point.
    double _cam_near; //Near view point of camera.
    double _cam_far;  //Fair view point of camera.

    QMatrix4x4 _vp_transform; //The full transform of current view.
    void calculateVpTransform(); //Recalculate the transformation matrix.

    double _cam_distancePerDelta; //Distance to adjust view with mouse wheel changes.
    double _cam_radsPerPixelElev; //Radians of adjustment per pixel of mouse movement.
    double _cam_radsPerPixelAzi;  //Radians of adjustment per pixel of mouse movement.
    QVector2D _cam_last_mouse;    //Last point of mouse interaction.

    /** A helper method used to update the rotation of the camera
     *  after a movement event from the mouse with appropriate key
     *  presses combined.
     */
    void updateFromMouse(QVector2D neww, QVector2D prev);

    // Helper Methods
    /** pointTransform
     * Given a point, apply a transform matrix and return a new, transformed vector */
    QVector3D pointTransform(QVector3D point, QMatrix3x3 transform);

    /** invertMatrix
     * QMatrix3x3 does not support inversion OotB, so we created a helper to do so. */
    QMatrix3x3 invertMatrix(QMatrix3x3 matrix);

    /** A helper method that handles the drawing of all polygons in the OpenGL scene */
    void drawCube();

    /** A helper method to draw visual aids, including the axes and ground plane. */
    void drawAids();

    /** a utility to draw a line between two points. */
    void drawLine(double x0, double y0, double x1, double y1);

    /** Draws a vertex at the point x,y in Visual Space*/
    void drawVertex(double x, double y);

    /** A helper method which allows us to translate a mouse click to a point in our view space. */
    QVector3D translatePointToAbsoluteSpace(QVector3D point);

    /** a helper method which allows us to translate from our absolute space to the visual space */
    QVector3D translatePointToVisualSpace(QVector3D point);

    /** A helper method which translates UI mouse events to our absolute space. */
    QVector3D translateMouseToPoint(QMouseEvent *event);

    /** A helper method to compute the cross product of two three dimension vectors. */
    QVector3D crossProduct(QVector3D a, QVector3D b);

    /** A helper which allows a vector to be rotated around the Z axis in absolute space. **/
    QVector3D RotateZ(QVector3D vec, double radians);

    /** A helper which allows a vector to be rotated around the Z axis in absolte space. **/
    QVector3D RotateY(QVector3D vec, double radians);

};

#endif // BASICOPENGLVIEW_H

