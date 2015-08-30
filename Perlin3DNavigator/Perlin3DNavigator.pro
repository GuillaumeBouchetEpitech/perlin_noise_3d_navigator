#-------------------------------------------------
#
# Project created by QtCreator 2014-05-04T20:51:55
#
#-------------------------------------------------

QT       += core gui
QT       += opengl



QMAKE_CXXFLAGS += -std=c++11


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Perlin3DNavigator
TEMPLATE = app

###

SOURCES += \
    main.cpp\
    perlin3d_chunk.cpp \
    glheader.cpp \
    t_shader_perlin3d.cpp \
    navigator_globalvalue.cpp \
    chunkgenerator.cpp \
    geometry/abstract_geometry.cpp

SOURCES += \
    widgets/Abstract_GLWidget.cpp \
    widgets/FreeFlyCameraWidget.cpp \
    widgets/chunkpropertieswidget.cpp \
    widgets/perlin3dviewerwidget.cpp \
    widgets/mainwindow.cpp

SOURCES += \
    geometry/geometry_box.cpp \
    geometry/geometry_hud_frustum.cpp \
    geometry/geometry_hud_grid.cpp \
    geometry/t_vertex.cpp

SOURCES += \
    utils/PerlinNoise.cpp \
    utils/Randomizer.cpp

###

HEADERS  += \
    perlin3d_chunk.h \
    glheader.h \
    Core3_2_context.h \
    t_shader_perlin3d.h \
    navigator_globalvalue.h \
    chunkgenerator.h \
    geometry/abstract_geometry.h

HEADERS  += \
    widgets/Abstract_GLWidget.hpp   \
    widgets/FreeFlyCameraWidget.hpp \
    widgets/perlin3dviewerwidget.h  \
    widgets/chunkpropertieswidget.h \
    widgets/mainwindow.h

HEADERS  += \
    geometry/geometry_box.h \
    geometry/geometry_hud_frustum.h \
    geometry/geometry_hud_grid.h \
    geometry/t_vertex.h

HEADERS  += \
    utils/PerlinNoise.hpp \
    utils/Randomizer.hpp

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

###

FORMS    +=


LIBS += -LGLEW

win32{
    INCLUDEPATH *= "C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A\Include"
    LIBS *= "C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A\Lib\glew32.lib"

    CONFIG(release, debug|release): LIBS += -L$$PWD/../myGL/build/Debug/release/ -lmyGL
    CONFIG(debug,   debug|release): LIBS += -L$$PWD/../myGL/build/Debug/debug/ -lmyGL
}

unix{
#    LIBS += -L$$PWD/../myGL/build/Debug/ -lmyGL
#    LIBS += -L$$PWD/../myGL -lmyGL
#   LIBS += $$PWD/../myGL/libmyGL.so.1.0.0
    LIBS += -lGLEW
}


INCLUDEPATH += $$PWD/../myGL
DEPENDPATH += $$PWD/../myGL

OTHER_FILES +=          \
    TODOLIST.txt \
    shaders/test_150.vert \
    shaders/test_150.frag \
    shaders/test_100.frag \
    shaders/test_100.vert

