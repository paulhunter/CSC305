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

    this->_cam_azimuth = 0.523;
    this->_cam_distance = 30;
    this->_cam_elevation = 0.785;
    this->_cam_near = 10;
    this->_cam_far = 1000;

    this->_cam_radsPerPixelAzi = 0.0014;
    this->_cam_radsPerPixelElev = 0.0014;
    this->_cam_distancePerDelta = 25;
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
    QVector2D point = QVector2D(event->x(),event->y());
    if(event->button() == Qt::LeftButton)
    {
        //On Left Button, we translate through the space.
    }
    else if(event->button() == Qt::RightButton)
    {
        qDebug() << "RMB Down";
        _mouseButtonDown = true;
        _cam_last_mouse = point;
        //If a right button, we're modifying Azimuth and Elevation, so we
        //track the point for movement.
    }
    update(); //We want to update regardless of button for 'click to refresh'
}

void BasicOpenGLView::mouseMoveEvent(QMouseEvent *event)
{
    if(!_mouseButtonDown)
    {
        //Nothing to do.
        return;
    }

    QVector2D point = QVector2D(event->x(),event->y());
    if(event->buttons() & Qt::RightButton)
    {
        //Update camera position azimuth and elevation.
        updateFromMouse(point, _cam_last_mouse);
        _cam_last_mouse = point;
    }
    update();
}

void BasicOpenGLView::mouseReleaseEvent(QMouseEvent *event)
{
    if(!_mouseButtonDown)
    {
        //nothing to do;
    }

    QVector2D point = QVector2D(event->x(), event->y());
    if(event->button() == Qt::RightButton)
    {
        updateFromMouse(point, _cam_last_mouse);
        _cam_last_mouse = point;
        _mouseButtonDown = false;
        qDebug() << "RMB Released";
    }
}

void BasicOpenGLView::wheelEvent(QWheelEvent * event)
{
    if(event->orientation() == Qt::Vertical){
        _cam_distance += event->delta() * _cam_distancePerDelta;
        _cam_distance = std::min(MAX_CAM_DIS, std::max(MIN_CAM_DIS, _cam_distance));
        update();
    }
}

// ////////////////////////////////////
// CAMERA CONTROL HELPERS
// ///////////////////////////////////

void BasicOpenGLView::SetCameraPosition(double azimuth, double elevation, double distance)
{
    _cam_azimuth = azimuth;
    _cam_azimuth = std::min(MAX_CAM_AZI, std::max(MIN_CAM_AZI, _cam_azimuth));
    _cam_elevation = elevation;
    _cam_distance = distance;
    _cam_distance = std::min(MAX_CAM_DIS, std::max(MIN_CAM_DIS, _cam_distance));
}

void BasicOpenGLView::updateFromMouse(QVector2D neww, QVector2D prev)
{
    //calculate change and bound azimuth
    _cam_azimuth += (neww.x() - prev.x()) * _cam_radsPerPixelAzi;
    _cam_azimuth = std::min(MAX_CAM_AZI, std::max(MIN_CAM_AZI, _cam_azimuth));
    qDebug() << "Camera Azimuth: " << _cam_azimuth;
    //calculate elevation change, no wrap needed?, trig functions will handle it.
    _cam_elevation += (neww.y() - prev.y()) * _cam_radsPerPixelElev;
    qDebug() << "Camera Elevation: " << _cam_elevation;
}

// /////////////////////////////////////
// SCENE OBJECT INITIALIZERS
// /////////////////////////////////////
void BasicOpenGLView::initCube()
{
    this->_cube = QVector< QVector<QVector4D> >();
    this->_cube_panel_colors = QVector <QVector3D>();
    QVector4D a, b, c, d, e, f, g, h; //The eight points of the cube.
    double cs = 5; //length of half side.
    a = QVector4D( cs,    0,  cs, 1);
    b = QVector4D(-cs,    0,  cs, 1);
    c = QVector4D(-cs,    0, -cs, 1);
    d = QVector4D( cs,    0, -cs, 1);
    e = QVector4D( cs, cs*2,  cs, 1);
    f = QVector4D(-cs, cs*2,  cs, 1);
    g = QVector4D(-cs, cs*2, -cs, 1);
    h = QVector4D( cs, cs*2, -cs, 1);

    //Add our twelve triangles.
    _cube.append(QVector<QVector4D>());
    _cube.last().append(a);
    _cube.last().append(b);
    _cube.last().append(d);
    _cube.append(QVector<QVector4D>());
    _cube.last().append(b);
    _cube.last().append(c);
    _cube.last().append(d);

    _cube.append(QVector<QVector4D>());
    _cube.last().append(d);
    _cube.last().append(e);
    _cube.last().append(h);
    _cube.append(QVector<QVector4D>());
    _cube.last().append(d);
    _cube.last().append(c);
    _cube.last().append(h);

    _cube.append(QVector<QVector4D>());
    _cube.last().append(c);
    _cube.last().append(b);
    _cube.last().append(g);
    _cube.append(QVector<QVector4D>());
    _cube.last().append(g);
    _cube.last().append(h);
    _cube.last().append(c);

    _cube.append(QVector<QVector4D>());
    _cube.last().append(a);
    _cube.last().append(b);
    _cube.last().append(g);
    _cube.append(QVector<QVector4D>());
    _cube.last().append(a);
    _cube.last().append(f);
    _cube.last().append(g);

    _cube.append(QVector<QVector4D>());
    _cube.last().append(a);
    _cube.last().append(d);
    _cube.last().append(e);
    _cube.append(QVector<QVector4D>());
    _cube.last().append(a);
    _cube.last().append(d);
    _cube.last().append(f);

    _cube.append(QVector<QVector4D>());
    _cube.last().append(f);
    _cube.last().append(g);
    _cube.last().append(e);
    _cube.append(QVector<QVector4D>());
    _cube.last().append(e);
    _cube.last().append(h);
    _cube.last().append(g);

    int x;
    for(x = 0; x < 12; x++)
    {
        _cube_panel_colors.append(QVector3D());
        _cube_panel_colors.last().setX(rand()/(RAND_MAX*1.0f));
        _cube_panel_colors.last().setY(rand()/(RAND_MAX*1.0f));
        _cube_panel_colors.last().setZ(rand()/(RAND_MAX*1.0f));
    }

}

// ////////////////////////////////////
// TRANSFORM BUILDERS/HELPERS
// /////////////////////////////////////

void BasicOpenGLView::calculateVpTransform()
{
    //Calculate the Camera Location, Gaze vector, etc.
    QVector3D cam_pos = QVector3D((qreal)0, (qreal)_cam_distance, (qreal)0);
    cam_pos = RotateZ(cam_pos, _cam_elevation);
    cam_pos = RotateY(cam_pos, _cam_azimuth);
    //cam_pos is our 'e', location of the eye.
    qDebug() << "cam_pos: (" << cam_pos.x() << ", " << cam_pos.y() << ", "
             << cam_pos.z() << ")";

    QVector3D view_up = QVector3D(0.0 ,1.0 ,0.0 );
    view_up = RotateZ(view_up, _cam_elevation);
    view_up = RotateY(view_up, _cam_azimuth);

    qDebug() << "view_up: (" << view_up.x() << ", " << view_up.y() << ", "
             << view_up.z() << ")";

    QVector3D gaze_dir = -1 * cam_pos;
    gaze_dir.normalize();
    //TODO: Apply translation , AFTER getting gaze direction.
    //<INSERT MISSING TRANSLATION CODE>

    //We can now calculate our coordinate reference frame
    //for our canonical view volume.
    QVector3D w = -1 * gaze_dir;
    QVector3D u = this->crossProduct(view_up, w);
    //do not need to normalize u as w and view_up are unit vectors.
    QVector3D v = this->crossProduct(w, u);

    //Todo: Calculate
    QMatrix4x4 mo;
    QMatrix4x4 temp;
    temp.setToIdentity();
    mo.setToIdentity();
    //along negative Z axis.
    double n = -_cam_near;
    double f = -_cam_far;
    //Width is set to FOV, height is adjusted accordingly.
    double l = tan(CAM_FOV/2.0)*n; //negative x axis.
    double r = -l;
    double t = r * (this->height()/(this->width()*1.0));
    double b = -t;
    double nx = this->width();
    double ny = this->height();

    temp.operator ()(0,0) = nx/2.0;
    temp.operator ()(1,1) = ny/2.0;
    temp.operator ()(0,3) = (nx-1)/2.0;
    temp.operator ()(1,3) = (ny-1)/2.0;

    mo = mo * temp;

    temp.setToIdentity();
    temp.operator ()(0,0) = 2.0/(r-l);
    temp.operator ()(1,1) = 2.0/(t-b);
    temp.operator ()(2,2) = 2.0/(n-f);

    mo = mo * temp;

    temp.setToIdentity();
    temp.operator ()(0,3) = -(l+r)/2.0;
    temp.operator ()(1,3) = -(b+t)/2.0;
    temp.operator ()(2,3) = -(n+f)/2.0;

    mo = mo * temp;

    //Calculate View through two matrices.
    QMatrix4x4 mv;
    QMatrix4x4 mv_2;
    mv.operator ()(0,0) = u.x();
    mv.operator ()(0,0) = u.y();
    mv.operator ()(0,0) = u.z();
    mv.operator ()(1,0) = v.x();
    mv.operator ()(1,1) = v.y();
    mv.operator ()(1,2) = v.z();
    mv.operator ()(2,0) = w.x();
    mv.operator ()(2,1) = w.y();
    mv.operator ()(2,2) = w.z();
    mv.operator ()(3,3) = 1;

    mv_2.setToIdentity();
    mv_2.operator ()(0,3) = -cam_pos.x();
    mv_2.operator ()(1,3) = -cam_pos.y();
    mv_2.operator ()(2,3) = -cam_pos.z();

    mv = mv * mv_2;

    //Calculate Projection Transform
    QMatrix4x4 mp;
    mp.setToIdentity();
    mp.operator ()(3,3) = 0.0;
    mp.operator ()(2,3) = -1 * this->_cam_far;
    mp.operator ()(2,2) = (this->_cam_near + this->_cam_far) / this->_cam_near;
    mp.operator ()(3,2) = (1.0 / this->_cam_near);

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

    //Draw CUBE
    int tcount = _cube.count();
    int x;
    QVector4D a,b,c, color;
    for(x = 0; x < tcount; x++)
    {
        a = _vp_transform * _cube.at(x).at(0);
        b = _vp_transform * _cube.at(x).at(1);
        c = _vp_transform * _cube.at(x).at(2);
        color = _cube_panel_colors.at(x);

        glBegin(GL_TRIANGLES);
        glColor3f(color.x(), color.y(), color.z());
        glVertex3f(a.x(), a.y(), a.z());
        glVertex3f(b.x(), b.y(), b.z());
        glVertex3f(c.x(), c.y(), c.z());
        glEnd();
    }
}

void BasicOpenGLView::drawAids()
{
    double ad = 100;
    QVector4D x1, x2, y1, y2, z1, z2;
    x1 = _vp_transform * QVector4D( ad,  0,   0, 1);
    x2 = _vp_transform * QVector4D(-ad,  0,   0, 1);
    y1 = _vp_transform * QVector4D(0,   ad,   0, 1);
    y2 = _vp_transform * QVector4D(0,  -ad,   0, 1);
    z1 = _vp_transform * QVector4D(0,    0,  ad, 1);
    z2 = _vp_transform * QVector4D(0,    0, -ad, 1);

    //Draw X axis.
    glBegin(GL_LINES);
    glColor3f(0.5, 0.2, 0.2);
    glVertex3f(x1.x(), x1.y(), x1.z());
    glVertex3f(x2.x(), x2.y(), x2.z());
    glEnd();

    //Draw Y axis.
    glBegin(GL_LINES);
    glColor3f(0.2, 0.2, 0.5);
    glVertex3f(y1.x(), y1.y(), y1.z());
    glVertex3f(y2.x(), y2.y(), y2.z());
    glEnd();

    //Draw Z axis.
    glBegin(GL_LINES);
    glColor3f(0.2, 0.5, 0.2);
    glVertex3f(z1.x(), z1.y(), z1.z());
    glVertex3f(z2.x(), z2.y(), z2.z());
    glEnd();
}

void BasicOpenGLView::drawLine(double x0, double y0, double x1, double y1)
{
    qDebug() << "Drawing line from " << x0 << "," << y0 << " to " << x1 << "," << y1;
    glBegin(GL_LINES);
    glVertex2f(x0, y0);
    glVertex2f(x1, y1);
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

QVector3D BasicOpenGLView::crossProduct(QVector3D a, QVector3D b)
{
    //Cross product as per class notes. Could also have been done
    //with a Matrix.
    return QVector3D(
                (a.y()*b.z())-(a.z()*b.y()),
                (a.z()*b.x())-(a.x()*b.z()),
                (a.x()*b.y())-(a.y()*b.x()));
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

    QVector3D r = pointTransform(vec, m);
    qDebug() << "RotateZ: In: (" << vec.x() << ", " << vec.y()\
             << ", " << vec.z() << "), angle: " << radians\
             << " out: (" << r.x() << ", " << r.y() << ", " << r.z() << ")";
    return r;
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

    QVector3D r = this->pointTransform(vec, m);
    qDebug() << "RotateY: In: (" << vec.x() << ", " << vec.y()\
             << ", " << vec.z() << "), angle: " << radians\
             << " out: (" << r.x() << ", " << r.y() << ", " << r.z() << ")";
    return r;
}
