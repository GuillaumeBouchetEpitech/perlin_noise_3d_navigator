
#ifndef GEOMETRY_HUD_GRID_H
#define GEOMETRY_HUD_GRID_H


#include "t_vertex.h"

#include "../myGL/GL_Matrix.hpp"


#include "abstract_geometry.h"


class   Geometry_HUD_Grid : public Abstract_Geometry
{
private :
    float           _sideSize;
public :
    void            setSideSize(float sideSize);
    inline float    getSideSize() const { return (_sideSize); }

public :
    Geometry_HUD_Grid( t_Shader_Perlin3D& shader );

public :
    void    generate();
    void    render( const myGL::GL_Matrix& modelviewMatrix,
                    const myGL::Vec3f& camera_pos );
};


#endif // GEOMETRY_HUD_GRID_H
