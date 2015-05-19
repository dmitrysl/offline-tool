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
    parser/cronossitexmlparser.cpp \
    generator/exportcronossitexmlgenerator.cpp \
    parser/importxmlvalidator.cpp \
    parser/exportxmlfilevalidationmessagehandler.cpp \
    dialog/aboutdialog.cpp \
    dialog/selecttimezonedialog.cpp \
    utils.cpp

HEADERS  += mainwindow.h \
    entities.h \
    parser/cronossitexmlparser.h \
    generator/exportcronossitexmlgenerator.h \
    parser/importxmlvalidator.h \
    parser/exportxmlfilevalidationmessagehandler.h \
    dialog/aboutdialog.h \
    dialog/selecttimezonedialog.h \
    utils.h

FORMS    += mainwindow.ui \
    dialog/aboutdialog.ui \
    dialog/selecttimezonedialog.ui

DISTFILES +=

RESOURCES += \
    resources.qrc
