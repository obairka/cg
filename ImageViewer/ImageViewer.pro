#-------------------------------------------------
#
# Project created by QtCreator 2014-04-02T16:15:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageViewer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    triangle/triangle.cpp \
    canvas.cpp \
    triangle/texture.cpp \
    triangle/edge.cpp \
    triangle/texturedpoint.cpp \
    drawpanel.cpp \
    square.cpp \
    sizecontroller.cpp \
    doubleslider.cpp \


HEADERS  += mainwindow.h \
    triangle/triangle.h \
    triangle/edge.h \
    triangle/texturedpoint.h \
    triangle/texture.h \
    canvas.h \
    drawpanel.h\
    square.h \
    sizecontroller.h \
    doubleslider.h \
    triangle/filter.h
