/*
 * basicopenglview.h
 *
 * Created by: Brian Wyvill
 * Last Author: Paul Hunter
 *
 * CSC 305 - Assignment 1 - Homogeneous Coordinates and Matrices
 *
 * BasicOpenGLView is a QWidget that allows users to draw polygons
 * within an 2D OpenGL scene. Users can then apply transformations
 * by stacking them into a working transform.
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
#define MAX_CAM_AZI 1.57
#define MIN_CAM_AZI 0.0

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

    //Scene Graph?

    //Camera Info
    double _cam_azimuth; //0 - 2*pi radians, measured from the X Axis
    double _cam_elevation; //0-90 Degrees, measure from the XZ Plane
    double _cam_distance; //Distance from the view point.
    double _cam_near;
    double _cam_far;

    QMatrix4x4 _vp_transform; //The full transform of our view.
    void calculateVpTransform();

    double _cam_radsPerPixelElev;
    double _cam_radsPerPixelAzi;
    QVector2D _cam_last_mouse;
    bool _cam_aziC; //Changing in Azimuth
    bool _cam_eleC; //Changing in Elevation

    //A helper method used to update the rotation of the camera
    //after a movement event from the mouse with appropriate key
    //presses combined.
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

    /** A helper which allows a vector to be rotated around the Z axis in absolute space. **/
    QVector3D RotateZ(QVector3D vec, double radians);

    /** A helper which allows a vector to be rotated around the Z axis in absolte space. **/
    QVector3D RotateY(QVector3D vec, double radians);

};

#endif // BASICOPENGLVIEW_H

