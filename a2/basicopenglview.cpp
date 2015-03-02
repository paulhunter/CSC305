/*
 * basicopenglview.cpp
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

#include "basicopenglview.h"

// //////////////////////////////////
// PUBLIC METHODS
// //////////////////////////////////
BasicOpenGLView::BasicOpenGLView(QWidget *parent) : QGLWidget(parent)
{
    //Prep Polygon Creation and Storage Vars
    _mouseButtonDown = false;
    srand(time(NULL));

    this->_cam_azimuth = 30;
    this->_cam_distance = 10;
    this->_cam_elevation = 45;

}

// END OF PUBLIC METHODS

void BasicOpenGLView::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glShadeModel( GL_FLAT );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glPointSize(5);
}

void BasicOpenGLView::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //As we did in class, we set our viewport with
    //convention UI schemes, 0,0 at the top left.
    glOrtho((GLdouble)0,
            (GLdouble)width,
            (GLdouble)0,
            (GLdouble)height,
            -10.0, 10.0);

    glMatrixMode(GL_MODELVIEW);
}

void BasicOpenGLView::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    calculateVpTransform();
    drawCube();
}
// ////////////////////////////////////////////
// MOUSE EVENTS
// /////////////////////////////////////////////
/* Called when a mouse button is pressed */
void BasicOpenGLView::mousePressEvent(QMouseEvent *event)
{
    if(_mouseButtonDown)
    {
        //If a button is already down, the additional button press means nothing
        return;
    }

    _mouseButtonDown = false;
    if(event->button() == Qt::LeftButton)
    {
        //On Left Button, we translate through the space.
    }
    else if(event->button() == Qt::RightButton)
    {
        //If a right button, we're modifying Azimuth and Elevation

    }
    update();
}

void BasicOpenGLView::mouseMoveEvent(QMouseEvent *event)
{
    //TODO: Implement Point Move to update drawings.
}

void BasicOpenGLView::mouseReleaseEvent(QMouseEvent *event)
{
    //TODO: Implement Finalize Point Move
}

// ////////////////////////////////////
// TRANSFORM BUILDERS/HELPERS
// /////////////////////////////////////

void BasicOpenGLView::calculateVpTransform()
{

    //Calculate the Camera Location, Gaze vector, etc.
    QVector3D cam_pos = QVector3D((qreal)0, (qreal)1, (qreal)0);


    //Todo: Calculate
    QMatrix4x4 mo;
    mo.setToIdentity();

    //Calculate View
    QMatrix4x4 mv;
    mo.setToIdentity();

    //Calculate Projection
    QMatrix4x4 mp;
    mp.setToIdentity();
    mp.operator ()(3,3) = 0;
    mp.operator ()(2,3) = -1 * this->_cam_far;
    mp.operator ()(2,2) = (this->_cam_near + this->_cam_far) / this->_cam_near;
    mp.operator ()(3,2) = (1.0f / this->_cam_near);

    this->_vp_transform.setToIdentity();
    this->_vp_transform = this->_vp_transform * mo;
    this->_vp_transform = this->_vp_transform * mv;
    this->_vp_transform = this->_vp_transform * mp;

}

// //////////////////////////////////
// UI Drawing Helpers
// //////////////////////////////////

void BasicOpenGLView::drawCube()
{
    //This is the bare minimum, we brute force draw a cube
    //in the scene. If time permits I wish to integrate
    //scenegraphs.

    int x0, y0, x1, y1, i, j;
    QVector3D vsp; //visual space point

    /* Polygon Drawing Code.
    for(i = 0; i < polyCount; i++)
    {
        if(_userPolygons.at(i).size() == 0)
            continue; //Skip any empty polygons that happened to get in here..

        //Set the draw color to that of the polygon
        glColor3f(_userPolygonColours[i][0],_userPolygonColours[i][1],_userPolygonColours[i][2]);
        //glColor3f(0.5f, 0.5f, 0.5f) - Debug Grey
        vsp = translatePointToVisualSpace(_userPolygons.at(i).at(0));
        if(_userPolygons.at(i).size() <= 1)
        {
            //The polygon has a single point.

            drawVertex(vsp.x(), vsp.y());
        }
        else
        {
            //The polygon has two or more points.'
            int vCount = _userPolygons.at(i).size();
            x0 = vsp.x();
            y0 = vsp.y();

            for(j = 1; j < vCount; j++)
            {
                vsp = translatePointToVisualSpace(_userPolygons.at(i).at(j));
                x1 = vsp.x();
                y1 = vsp.y();
                drawLine(x0, y0, x1, y1);
                drawVertex(x0, y0);
                x0 = x1;
                y0 = y1;
            }

            if(vCount > 2)
            {
                //If the polygon has three or more points we want to close it over,
                //drawing a line between the
                vsp = translatePointToVisualSpace(_userPolygons.at(i).at(0));
                drawLine(x0, y0, vsp.x(), vsp.y());
                drawVertex(vsp.x(), vsp.y());
            }
            //In either case we need to draw the last vertex.
            drawVertex(x0, y0);
        }
    }
    */
}

void BasicOpenGLView::drawLine(double x0, double y0, double x1, double y1)
{
    qDebug() << "Drawing line from " << x0 << "," << y0 << " to " << x1 << "," << y1;
    glBegin(GL_LINES);
    glVertex2f(x0, y0);
    glVertex2f(x1, y1);
    glEnd();
}

void BasicOpenGLView::drawVertex(double x, double y)
{
    qDebug() << "Drawing Vertex at " << x << "," << y;
    int i;
    GLfloat circcoords[100][2];
    //Create a circle around the point provided with the
    //Vertex radius defined in the header file.
    for(i = 0; i < 100; i++)
    {
        circcoords[i][0]= (GLfloat)(V_RADIUS * cos(i*2*M_PI/100.0) + x);
        circcoords[i][1]= (GLfloat)(V_RADIUS * sin(i*2*M_PI/100.0) + y);
    }

    //Draw the point.
    glBegin(GL_POLYGON);
    for(i = 0; i < 100; i++)
    {
        glVertex2f(circcoords[i][0], circcoords[i][1]);
    }
    glEnd();

}

// /////////////////////////////////
// Matrix and Transform Helpers
// //////////////////////////////////
QVector3D BasicOpenGLView::translatePointToAbsoluteSpace(QVector3D point)
{
    QVector3D result = point;

    //TODO? Likely not, we have no reason to know where in the space, the
    //mouse clicked.

    result.setZ(1);
    return result;
}

QVector3D BasicOpenGLView::translatePointToVisualSpace(QVector3D point)
{
    QVector3D result = point;

    //TODO - Apply View matrix.

    result.setZ(1);
    return result;
}

QVector3D BasicOpenGLView::translateMouseToPoint(QMouseEvent *event)
{

    //We use the same formula used to set the ortho from of the OpenGL.
    //Top left is 0,0.
    QVector3D result = QVector3D( event->x(), event->y(), 1);
    qDebug() << "Mouse Click at " << result.x() << ", " << result.y() << ".";
    return result;
}

QVector3D BasicOpenGLView::pointTransform(QVector3D point, QMatrix3x3 transform)
{
    //Matrix Vector Multiplication - http://www.facstaff.bucknell.edu/mastascu/elessonsHTML/Circuit/MatVecMultiply.htm
    QVector3D result = QVector3D();
    result.setX( ((transform.operator ()(0,0)) * point.x()) + ((transform.operator ()(0,1)) * point.y()) + ((transform.operator ()(0,2)) * point.z()) );
    result.setY( ((transform.operator ()(1,0)) * point.x()) + ((transform.operator ()(1,1)) * point.y()) + ((transform.operator ()(1,2)) * point.z()) );
    result.setZ( ((transform.operator ()(2,0)) * point.x()) + ((transform.operator ()(2,1)) * point.y()) + ((transform.operator ()(2,2)) * point.z()) );
    return result;
}

QMatrix3x3 BasicOpenGLView::invertMatrix(QMatrix3x3 matrix)
{
    QMatrix3x3 result = QMatrix3x3();

     //Calculate the determinate of the matrix - http://www.mathworks.com/help/aeroblks/determinantof3x3matrix.html
    double det = (\
                 (matrix.operator ()(0,0) * ((matrix.operator ()(1,1) * matrix.operator ()(2,2)) - (matrix.operator ()(1,2) * matrix.operator ()(2,1)) ) ) + \
                 (matrix.operator ()(0,1) * ((matrix.operator ()(1,2) * matrix.operator ()(2,0)) - (matrix.operator ()(1,0) * matrix.operator ()(2,2)) ) ) + \
                 (matrix.operator ()(0,2) * ((matrix.operator ()(1,0) * matrix.operator ()(2,1)) - (matrix.operator ()(1,1) * matrix.operator ()(2,0)) ) ) );

    //Construct inverse - http://mathworld.wolfram.com/MatrixInverse.html
    result.operator ()(0,0) = (((matrix.operator ()(1,1) * matrix.operator ()(2,2)) - (matrix.operator ()(1,2) * matrix.operator ()(2,1))) / det);
    result.operator ()(0,1) = (((matrix.operator ()(0,2) * matrix.operator ()(2,1)) - (matrix.operator ()(0,1) * matrix.operator ()(2,2))) / det);
    result.operator ()(0,2) = (((matrix.operator ()(0,1) * matrix.operator ()(1,2)) - (matrix.operator ()(0,2) * matrix.operator ()(1,1))) / det);
    result.operator ()(1,0) = (((matrix.operator ()(1,2) * matrix.operator ()(2,0)) - (matrix.operator ()(1,0) * matrix.operator ()(2,2))) / det);
    result.operator ()(1,1) = (((matrix.operator ()(0,0) * matrix.operator ()(2,2)) - (matrix.operator ()(0,2) * matrix.operator ()(2,0))) / det);
    result.operator ()(1,2) = (((matrix.operator ()(0,2) * matrix.operator ()(1,0)) - (matrix.operator ()(0,0) * matrix.operator ()(1,2))) / det);
    result.operator ()(2,0) = (((matrix.operator ()(1,0) * matrix.operator ()(2,1)) - (matrix.operator ()(1,1) * matrix.operator ()(2,0))) / det);
    result.operator ()(2,1) = (((matrix.operator ()(0,1) * matrix.operator ()(2,0)) - (matrix.operator ()(0,0) * matrix.operator ()(2,1))) / det);
    result.operator ()(2,2) = (((matrix.operator ()(0,0) * matrix.operator ()(1,1)) - (matrix.operator ()(0,1) * matrix.operator ()(1,0))) / det);

    return result;
}

QVector3D BasicOpenGLView::RotateZ(QVector3D vec, double radians)
{
    double cosA = (double)cos(radians);
    double sinA = (double)sin(radians);

    QMatrix3x3 m;
    m.operator ()(0,0) = cosA;
    m.operator ()(0,1) = -sinA;
    m.operator ()(1,0) = sinA;
    m.operator ()(1,1) = cosA;
    m.operator ()(2,2) = 1;

    return this->pointTransform(vec, m);
}

QVector3D BasicOpenGLView::RotateY(QVector3D vec, double radians)
{
    double cosA = (double)cos(radians);
    double sinA = (double)sin(radians);

    QMatrix3x3 m;
    m.operator ()(0,0) = cosA;
    m.operator ()(0,2) = sinA;
    m.operator ()(1,1) = 1;
    m.operator ()(2,0) = -sinA;
    m.operator ()(2,2) = cosA;

    return this->pointTransform(vec, m);
}
