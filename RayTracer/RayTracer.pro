#-------------------------------------------------
#
# Project created by QtCreator 2015-03-23T21:58:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RayTracer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sphere.cpp \
    sceneobjectprops.cpp \
    scenemanager.cpp \
    scenegraphnode.cpp \
    raytracer.cpp \
    ray.cpp

HEADERS  += mainwindow.h \
    sphere.h \
    sceneobjectprops.h \
    sceneobject.h \
    scenemanager.h \
    scenegraphnode.h \
    raytracer.h \
    ray.h \
    lightsource.h

FORMS    += mainwindow.ui
