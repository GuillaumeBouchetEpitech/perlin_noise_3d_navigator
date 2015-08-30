
#ifndef GEOMETRY_HUD_GRID_H
#define GEOMETRY_HUD_GRID_H


#include "t_vertex.h"

#include "GL_Matrix.hpp"


#include "abstract_geometry.h"


class   Geometry_HUD_Grid : public Abstract_Geometry
{
private :
    float           _sideSize;
public :
    void            setSideSize(float sideSize);
    inline float    getSideSize() const { return (_sideSize); }

private :
    enum {
        eVAO_Grid = 0,
        eVAO_Count
    };

    enum {
        eVBO_Grid_vertices = 0,
        eVBO_Grid_indices,
        eVBO_Count
    };

private :
    GLuint  _pGridVertexArrayObject_IDs[eVAO_Count];
    GLuint  _pGridVertexBufferObject_IDs[eVBO_Count];

    t_Vertices  _gridVertices;
    t_Indices   _gridIndices;

public :
    Geometry_HUD_Grid( t_Shader_Perlin3D& shader );
    ~Geometry_HUD_Grid();

public :
    void    generate();
    void    render( const myGL::GL_Matrix& modelviewMatrix,
                    const myGL::Vec3f& camera_pos );
};


#endif // GEOMETRY_HUD_GRID_H
