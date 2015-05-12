#-------------------------------------------------
#
# Project created by QtCreator 2015-05-08T23:23:43
#
#-------------------------------------------------

QT       += core gui
CONFIG += static c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CronosOffline
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cronossitexmlparser.cpp \
    exportcronossitexmlgenerator.cpp

HEADERS  += mainwindow.h \
    entities.h \
    cronossitexmlparser.h \
    exportcronossitexmlgenerator.h

FORMS    += mainwindow.ui