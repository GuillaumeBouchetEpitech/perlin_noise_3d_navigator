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

OBJECTS_DIR = ./obj
MOC_DIR = ./obj

###

SOURCES += \
    src/main.cpp\
    src/perlin3d_chunk.cpp \
    src/glheader.cpp \
    src/t_shader_perlin3d.cpp \
    src/navigator_globalvalue.cpp \
    src/chunkgenerator.cpp \
    src/geometry/abstract_geometry.cpp

SOURCES += \
    src/widgets/Abstract_GLWidget.cpp \
    src/widgets/FreeFlyCameraWidget.cpp \
    src/widgets/chunkpropertieswidget.cpp \
    src/widgets/perlin3dviewerwidget.cpp \
    src/widgets/mainwindow.cpp

SOURCES += \
    src/geometry/geometry_box.cpp \
    src/geometry/geometry_hud_frustum.cpp \
    src/geometry/geometry_hud_grid.cpp \
    src/geometry/t_vertex.cpp

SOURCES += \
    src/utils/PerlinNoise.cpp \
    src/utils/Randomizer.cpp

###

HEADERS  += \
    src/perlin3d_chunk.h \
    src/glheader.h \
    src/Core3_2_context.h \
    src/t_shader_perlin3d.h \
    src/navigator_globalvalue.h \
    src/chunkgenerator.h \
    src/geometry/abstract_geometry.h

HEADERS  += \
    src/widgets/Abstract_GLWidget.hpp   \
    src/widgets/FreeFlyCameraWidget.hpp \
    src/widgets/perlin3dviewerwidget.h  \
    src/widgets/chunkpropertieswidget.h \
    src/widgets/mainwindow.h

HEADERS  += \
    src/geometry/geometry_box.h \
    src/geometry/geometry_hud_frustum.h \
    src/geometry/geometry_hud_grid.h \
    src/geometry/t_vertex.h

HEADERS  += \
    src/utils/PerlinNoise.hpp \
    src/utils/Randomizer.hpp

###

SOURCES +=  \
    src/myGL/GL_FrustumCulling.cpp \
    src/myGL/GL_Math.cpp \
    src/myGL/GL_Matrix.cpp \
    src/myGL/GL_Vec2.inl \
    src/myGL/GL_Vec3.inl \
    src/myGL/GL_Vec4.inl \
    src/myGL/GL_FreeFlyController.cpp

HEADERS +=  \
    src/myGL/GL_FrustumCulling.hpp \
    src/myGL/GL_Math.hpp \
    src/myGL/GL_Matrix.hpp \
    src/myGL/GL_Vec2.hpp \
    src/myGL/GL_Vec3.hpp \
    src/myGL/GL_Vec4.hpp \
    src/myGL/GL_FreeFlyController.hpp

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
    LIBS += -lGLEW
}

INCLUDEPATH += $$PWD/src
DEPENDPATH += $$PWD/src


OTHER_FILES +=          \
    TODOLIST.txt \
    shaders/test_150.vert \
    shaders/test_150.frag \
    shaders/test_100.frag \
    shaders/test_100.vert

