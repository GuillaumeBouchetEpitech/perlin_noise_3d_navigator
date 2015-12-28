#ifndef T_SHADER_PERLIN3D_H
#define T_SHADER_PERLIN3D_H


#include "myGL/GL_Vec3.hpp"
#include "myGL/GL_Vec4.hpp"

#include "glheader.h"


struct          t_Shader_Perlin3D
{
    GLuint      _programm_id;

    GLuint      _location_a_vertex;
    GLuint      _location_a_color;
    GLuint      _location_a_normal;

    GLuint      _location_u_modelviewMatrix;
    GLuint      _location_u_projectionMatrix;
    GLuint      _location_u_mode;
    GLuint      _location_u_lightEnabled;

    GLuint      _location_u_perturbationEnabled;
    GLuint      _location_u_advance;

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

