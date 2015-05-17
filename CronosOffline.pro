#-------------------------------------------------
#
# Project created by QtCreator 2015-05-08T23:23:43
#
#-------------------------------------------------

QT       += core gui xmlpatterns
CONFIG += static c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CronosOffline
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cronossitexmlparser.cpp \
    exportcronossitexmlgenerator.cpp \
    delegate.cpp \
    importxmlvalidator.cpp \
    exportxmlfilevalidationmessagehandler.cpp \
    aboutdialog.cpp \
    selecttimezonedialog.cpp

HEADERS  += mainwindow.h \
    entities.h \
    cronossitexmlparser.h \
    exportcronossitexmlgenerator.h \
    delegate.h \
    importxmlvalidator.h \
    exportxmlfilevalidationmessagehandler.h \
    aboutdialog.h \
    selecttimezonedialog.h

FORMS    += mainwindow.ui \
    aboutdialog.ui \
    selecttimezonedialog.ui

DISTFILES +=

RESOURCES += \
    resources.qrc
