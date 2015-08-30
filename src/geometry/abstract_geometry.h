#ifndef ABSTRACT_GEOMETRY_H
#define ABSTRACT_GEOMETRY_H


#include "t_shader_perlin3d.h"


class   Abstract_Geometry
{
protected :
    t_Shader_Perlin3D&  _shader;

protected :
    bool    _isInitialized;
    bool    _VBO_and_VAO_initialized;

public:
    Abstract_Geometry( t_Shader_Perlin3D& );

};

#endif // ABSTRACT_GEOMETRY_H
