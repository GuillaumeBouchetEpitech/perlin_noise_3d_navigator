#ifndef GEOMETRY_BOX_H
#define GEOMETRY_BOX_H


#include "../myGL/GL_FreeFlyController.hpp"
#include "t_vertex.h"

#include "abstract_geometry.h"


class   Geometry_Box : public Abstract_Geometry
{
private :
    float       _sideSize;
public :
    void     setSideSize(float);
    inline float    getSideSize() const { return (_sideSize); }

public :
    Geometry_Box( t_Shader_Perlin3D& shader );

public :
    void        generate();
    void        bind();
    void        render();
    inline void unbind() const  { glBindVertexArray( 0 ); }

};


#endif // GEOMETRY_BOX_H

