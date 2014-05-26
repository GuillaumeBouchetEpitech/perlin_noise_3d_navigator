#ifndef T_SHADER_PERLIN3D_H
#define T_SHADER_PERLIN3D_H


#include "GL_Vec3.hpp"
#include "GL_Vec4.hpp"

#include "glheader.h"


struct  LightProperties
{
    myGL::Vec3f direction;
    myGL::Vec4f ambientColor;
    myGL::Vec4f diffuseColor;
    myGL::Vec4f specularColor;
};

struct  MaterialProperties
{
    myGL::Vec4f ambientColor;
    myGL::Vec4f diffuseColor;
    myGL::Vec4f specularColor;
    GLfloat     specularExponent;
};

struct  LightLocations
{
    GLint directionLocation;
    GLint ambientColorLocation;
    GLint diffuseColorLocation;
    GLint specularColorLocation;
};

struct  MaterialLocations
{
    GLint ambientColorLocation;
    GLint diffuseColorLocation;
    GLint specularColorLocation;
    GLint specularExponentLocation;
};

struct          t_Shader_Perlin3D
{
    GLuint      _programm_id;

    GLuint      _location_a_vertex;
    GLuint      _location_a_color;
    GLuint      _location_a_normal;

    GLuint      _location_u_modelviewMatrix;
    GLuint      _location_u_projectionMatrix;
    GLuint      _location_u_normalMatrix;
    GLuint      _location_u_mode;
    GLuint      _location_u_lightEnabled;

    GLuint      _location_u_perturbationEnabled;
    GLuint      _location_u_advance;

    LightLocations      _locations_light;
    MaterialLocations   _locations_material;

    LightProperties     _properties_light;
    MaterialProperties  _properties_material;

public :
    void    init();

public :
    bool    isAvailable_shader100();
    //bool    isAvailable_shader150();

private :
    void    prepareShaderProgram( const std::string& vertexShaderPath,
                                  const std::string& fragmentShaderPath );

};


#endif // T_SHADER_PERLIN3D_H

