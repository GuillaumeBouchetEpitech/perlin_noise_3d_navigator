#ifndef ABSTRACT_GEOMETRY_H
#define ABSTRACT_GEOMETRY_H


#include "t_shader_perlin3d.h"
#include "t_vertex.h"


class   Abstract_Geometry
{
protected:
    t_Shader_Perlin3D&  _shader;

protected:
    bool    _isInitialized;
    bool    _VBO_and_VAO_initialized;

protected:
    enum e_VBO_enum {
        eVBO_vertices = 0,
        eVBO_indices,
        eVBO_count
    };

    GLuint  _VAO_ID;
    GLuint  _pVBO_IDs[eVBO_count];

protected:
    t_Vertices  _vertices;
    t_Indices   _indices;

public:
    Abstract_Geometry( t_Shader_Perlin3D& );
    ~Abstract_Geometry();

public:
    void        generate();

};

#endif // ABSTRACT_GEOMETRY_H
