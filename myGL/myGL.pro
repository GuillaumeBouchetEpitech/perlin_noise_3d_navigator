#-------------------------------------------------
#
# Project created by QtCreator 2014-05-05T00:57:41
#
#-------------------------------------------------

QT       += opengl

QT       -= gui

TARGET = myGL
TEMPLATE = lib

DEFINES += MYGL_LIBRARY

SOURCES += \
    GL_FrustumCulling.cpp \
    GL_Math.cpp \
    GL_Matrix.cpp \
    GL_Vec2.inl \
    GL_Vec3.inl \
    GL_Vec4.inl \
    GL_FreeFlyController.cpp

HEADERS +=\
    GL_FrustumCulling.hpp \
    GL_Math.hpp \
    GL_Matrix.hpp \
    GL_Vec2.hpp \
    GL_Vec3.hpp \
    GL_Vec4.hpp \
    GL_FreeFlyController.hpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}
