#-------------------------------------------------
#
# Project created by QtCreator 2013-12-21T15:19:27
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Margaret
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Broken.cpp \
    Color.cpp \
    Figure.cpp \
    GroupsController.cpp \
    Line.cpp \
    Point.cpp \
    Polygon.cpp \
    Rectangle.cpp \
    ShapeController.cpp \
    Square.cpp

HEADERS  += mainwindow.h \
    Broken.h \
    Color.h \
    Figure.h \
    GroupsController.h \
    Line.h \
    Point.h \
    Polygon.h \
    Rectangle.h \
    ShapeController.h \
    Square.h

FORMS    += mainwindow.ui
