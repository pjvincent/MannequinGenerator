#-------------------------------------------------
#
# Project created by QtCreator 2014-06-13T11:18:38
#
#-------------------------------------------------

QT += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MannequinGenerator
TEMPLATE = app


SOURCES += \
    Main.cpp \
    Global.cpp \
    GLWidget.cpp \
    Group3D.cpp \
    MainWindow.cpp \
    Material.cpp \
    Object3D.cpp \
    Texture.cpp

HEADERS  += \
    Global.h \
    GLWidget.h \
    Group3D.h \
    MainWindow.h \
    Material.h \
    Object3D.h \
    Texture.h

OTHER_FILES += \
    fragment.glsl \
    geometry.glsl \
    vertex.glsl

RESOURCES += \
    Shaders.qrc
