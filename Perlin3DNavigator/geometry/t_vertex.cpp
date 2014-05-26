
#include "t_vertex.h"

t_Vertex::t_Vertex( const myGL::Vec3f& coord, const myGL::Vec3f& color)
    : _coord(coord), _color(color)
{}

t_Vertex::t_Vertex( const myGL::Vec3i& coord, const myGL::Vec3f& color)
    : _coord(coord.x, coord.y, coord.z), _color(color)
{}
