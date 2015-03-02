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
#include <QVector3D>        //A 3 element structure
#include <QStack>           //Stack implementation used for convenience
#include <QGenericMatrix>   //Generic Matrice Classes
#include <QMatrix>          //Matrix support methods.
#include <QMouseEvent>

#define V_RADIUS 5 //Vertex radius

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


private:
    //Mouse Controls + Polygon Modification
    bool _mouseButtonDown; //Mouse button pressed -> True
    bool _drawingPolygon; //Currently drawing a polygon -> True

    //Scene Graph?

    //Users Polygons

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
};

#endif // BASICOPENGLVIEW_H

