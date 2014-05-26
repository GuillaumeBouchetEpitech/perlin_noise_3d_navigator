#ifndef T_VERTEX_H
#define T_VERTEX_H


#include "GL_Vec3.hpp"

#include <vector>


struct  t_Vertex
{
    myGL::Vec3f _coord;
    myGL::Vec3f _color;
    myGL::Vec3f _normal;

    t_Vertex( const myGL::Vec3f& coord, const myGL::Vec3f& color);
    t_Vertex( const myGL::Vec3i& coord, const myGL::Vec3f& color);

};


typedef std::vector< t_Vertex >     t_Vertices;
typedef std::vector< unsigned int > t_Indices;


#endif // T_VERTEX_H
