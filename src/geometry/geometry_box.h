#ifndef GEOMETRY_BOX_H
#define GEOMETRY_BOX_H


#include "GL_FreeFlyController.hpp"
#include "t_vertex.h"

#include "abstract_geometry.h"


class   Geometry_Box : public Abstract_Geometry
{
private :
    float       _sideSize;
public :
    void     setSideSize(float);
    inline float    getSideSize() const { return (_sideSize); }

private :
    enum e_VAO_Box_enum {
        eVAO_Box = 0,
        eVAO_Count
    };

    enum e_VBO_Box_enum {
        eVBO_Box_vertices = 0,
        eVBO_Box_indices,
        eVBO_Count
    };

private :
    GLuint  _pBoxVertexArrayObject_IDs[eVAO_Count];
    GLuint  _pBoxVertexBufferObject_IDs[eVBO_Count];

    t_Vertices  _boxVertices;
    t_Indices   _boxIndices;

public :
    Geometry_Box( t_Shader_Perlin3D& shader );
    ~Geometry_Box();

public :
    void        generate();
    void        bind();
    void        render();
    inline void unbind() const  { glBindVertexArray( 0 ); }

};


#endif // GEOMETRY_BOX_H

