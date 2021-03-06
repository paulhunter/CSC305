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
    _drawingPolygon = false;
    srand(time(NULL));

    //Prep Transformations
    _applyTransforms = true;
    _transformStack = QStack<QMatrix3x3>();
    cleanTransformStack();
    _userPolygons = QVector< QVector<QVector3D> >();
    _userPolygonColours = QVector<QVector<double> >();
}

bool BasicOpenGLView::Drawing()
{
    return _drawingPolygon;
}

QMatrix3x3 BasicOpenGLView::CurrentTransform()
{
    return _transformStack.top();
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
    glOrtho(-(GLdouble)width/2.0,
            (GLdouble)width/2.0,
            -(GLdouble)height/2.0,
            (GLdouble)height/2.0,
            -10.0, 10.0);

    glMatrixMode(GL_MODELVIEW);
}

void BasicOpenGLView::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    drawPolygons();
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
    QVector3D p = translateMouseToPoint(event);
    p = translatePointToAbsoluteSpace(p);
    p.setZ(1);
    if(event->button() == Qt::LeftButton && _drawingPolygon)
    {
        //If a left button press and we are actively adding polygon, add it.
        _userPolygons.last().append(p);
        qDebug() << "Added Point to Polygon.";
    }
    else if(event->button() == Qt::RightButton)
    {
        //If a right button, select the point under the mouse.

    }
    update();
}

void BasicOpenGLView::mouseMoveEvent(QMouseEvent *event)
{
    //TODO: Implement Point Move
}

void BasicOpenGLView::mouseReleaseEvent(QMouseEvent *event)
{
    //TODO: Implement Finalize Point Move
}

// //////////////////////////////////
// Transform Stack Methods
// //////////////////////////////////
QMatrix3x3 BasicOpenGLView::PushMatrix(QMatrix3x3 matrix)
{
    QMatrix3x3 result;
    if(_transformStack.count() == 1)
    {
        result = _transformStack.top() * matrix;
    }
    else
    {
        result = _transformStack.pop() * matrix;
    }
    _transformStack.push(matrix);
    _transformStack.push(result);
    update();
    return result;
}

QMatrix3x3 BasicOpenGLView::PopMatrix()
{
    QMatrix3x3 result, newTop;
    if(_transformStack.count() == 1)
    {
        result.setToIdentity();
    }
    else
    {
        newTop = _transformStack.pop();
        newTop = newTop * invertMatrix(_transformStack.top());
        result = _transformStack.pop();
        _transformStack.push(newTop);
    }
    update();
    return result;
}

void BasicOpenGLView::ClearMatrixStack()
{
    cleanTransformStack();
}

// //////////////////////////////////
// Stack and Polygon Helpers
// //////////////////////////////////
void BasicOpenGLView::prepareNewPolygon()
{
    /* To prepare for drawing a new polygon we have to create space for it within
     * our list as well as randomly select a new color to assign to this polygon. */
    _userPolygons.append( QVector<QVector3D>() ); //Our new polygon, added to the end of the list.
    _userPolygonColours.append(QVector<double>(3));
    _userPolygonColours.last()[0] = (double)(rand() / (RAND_MAX*1.0f));
    _userPolygonColours.last()[1] = (double)(rand() / (RAND_MAX*1.0f));
    _userPolygonColours.last()[2] = (double)(rand() / (RAND_MAX*1.0f));
}

void BasicOpenGLView::cleanTransformStack()
{
    _transformStack.clear();
    QMatrix3x3 identity = QMatrix3x3();
    identity.setToIdentity();
    _transformStack.push(identity);
    update();
}

// //////////////////////////////////
// UI Drawing Helpers
// //////////////////////////////////

void BasicOpenGLView::drawPolygons()
{
    int x0, y0, x1, y1, i, j;
    int polyCount = _userPolygonColours.size();
    QVector3D vsp; //visual space point

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

// //////////////////////////////
// Slots
// ///////////////////////////////

void BasicOpenGLView::toggleMatrixApplication(bool toggleValue)
{
    _applyTransforms = toggleValue;
    update();
}

void BasicOpenGLView::togglePolygonDraw()
{
    if(_drawingPolygon)
    {
        qDebug() << "BOG: Closing Created Polygon";
        //We are already drawing a polygon, so attempt to close it
        if(_userPolygons.last().count() == 0)
        {
            //The user has opted to stop drawing a polygon before starting.
            //We will remove the empty polygon we added to the list.
            _userPolygons.remove(_userPolygons.count()-1);
            _userPolygonColours.remove(_userPolygonColours.count()-1);
        }
        _drawingPolygon = false;
    }
    else
    {
        qDebug() << "BOG: Opening Canvas for Drawing";
        //Start the drawing of a new polygon.
        prepareNewPolygon();
        _drawingPolygon = true;
    }
    update();
}

void BasicOpenGLView::clearAllPolygons()
{
    qDebug() << "BOG: Clearing Polygons";
    _drawingPolygon = false;
    _userPolygons.clear();
    _userPolygonColours.clear();
    update();
}


// /////////////////////////////////
// Matrix and Transform Helpers
// //////////////////////////////////
QVector3D BasicOpenGLView::translatePointToAbsoluteSpace(QVector3D point)
{
    QVector3D result = point;
    //In order to scale appropriately we have to know whether or not
    //we are applying view scaling or transformations in order to get back
    //to our reference space.
    if(_applyTransforms)
    {
        result = pointTransform(point, invertMatrix(_transformStack.top()));
    }
    //If we fall through each of the cases, and reach this point, we return
    //the original point we were given.
    result.setZ(1);
    return result;
}

QVector3D BasicOpenGLView::translatePointToVisualSpace(QVector3D point)
{
    QVector3D result = point;
    //Very similar to how we translate to absolute space, we apply the needed
    //transforms to the absolute space point to get back to our visual space.
    if(_applyTransforms)
    {
        result = pointTransform(point, _transformStack.top());
    }
    //If we fall through each of the cases, and reach this point, we return
    //the original point we were given.
    result.setZ(1);
    return result;
}

QVector3D BasicOpenGLView::translateMouseToPoint(QMouseEvent *event)
{
    //We use the same formula used to set the ortho from of the OpenGL.
    QVector3D result = QVector3D( (event->x()-(this->width()/2)), ((-1*event->y())+(this->height()/2)), 1);
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
