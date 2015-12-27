#include "geometry_box.h"


#include "perlin3d_chunk.h"


void    Geometry_Box::setSideSize(float sideSize)
{
    _sideSize = sideSize;
    _isInitialized = false;
}


Geometry_Box::Geometry_Box( t_Shader_Perlin3D& shader )
    : Abstract_Geometry( shader ),
      _sideSize(0)
{
}

void    Geometry_Box::generate()
{
    _isInitialized = true;

    _vertices.clear();
    _indices.clear();

    {

#define SIDE    ( _sideSize - 2 )
#define PUSH_BOX_VERTEX(l_X, l_Y, l_Z)   \
    _vertices.push_back( t_Vertex( myGL::Vec3f( \
    (l_X) * SIDE + 1,\
    (l_Y) * SIDE + 1,\
    (l_Z) * SIDE + 1),\
    myGL::Vec3f(1,1,1) ) )

        PUSH_BOX_VERTEX(0,0,0);
        PUSH_BOX_VERTEX(1,0,0);
        PUSH_BOX_VERTEX(1,1,0);
        PUSH_BOX_VERTEX(0,1,0);

        PUSH_BOX_VERTEX(0,0,1);
        PUSH_BOX_VERTEX(1,0,1);
        PUSH_BOX_VERTEX(1,1,1);
        PUSH_BOX_VERTEX(0,1,1);

#undef  PUSH_BOX_VERTEX
#undef  SIDE

        //_vertices.push_back( t_Vertex( myGL::Vec3f(SIDE * 0.5, SIDE * 0.5, SIDE * 0.5), myGL::Vec3f(1,1,1) ) );

#define SIDE        ( _sideSize )
#define HALF_SIDE   ( SIDE * 0.5f )

        _vertices.push_back( t_Vertex( myGL::Vec3f(HALF_SIDE, HALF_SIDE, SIDE / 8 * 3), myGL::Vec3f(1,1,1) ) );
        _vertices.push_back( t_Vertex( myGL::Vec3f(HALF_SIDE, HALF_SIDE, SIDE / 8 * 5), myGL::Vec3f(1,1,1) ) );

        _vertices.push_back( t_Vertex( myGL::Vec3f(HALF_SIDE, SIDE / 8 * 3, HALF_SIDE), myGL::Vec3f(1,1,1) ) );
        _vertices.push_back( t_Vertex( myGL::Vec3f(HALF_SIDE, SIDE / 8 * 5, HALF_SIDE), myGL::Vec3f(1,1,1) ) );

        _vertices.push_back( t_Vertex( myGL::Vec3f(SIDE / 8 * 3, HALF_SIDE, HALF_SIDE), myGL::Vec3f(1,1,1) ) );
        _vertices.push_back( t_Vertex( myGL::Vec3f(SIDE / 8 * 5, HALF_SIDE, HALF_SIDE), myGL::Vec3f(1,1,1) ) );

#undef  HALF_SIDE
#undef  SIDE




#define D_PUSH_LINE(l_i1, l_i2)     \
    _indices.push_back( l_i1 );  \
    _indices.push_back( l_i2 );

        D_PUSH_LINE(0, 1);
        D_PUSH_LINE(1, 2);
        D_PUSH_LINE(2, 3);
        D_PUSH_LINE(3, 0);

        D_PUSH_LINE(4, 5);
        D_PUSH_LINE(5, 6);
        D_PUSH_LINE(6, 7);
        D_PUSH_LINE(7, 4);

        D_PUSH_LINE(0, 4);
        D_PUSH_LINE(1, 5);
        D_PUSH_LINE(2, 6);
        D_PUSH_LINE(3, 7);

        D_PUSH_LINE( 8,  9);
        D_PUSH_LINE(10, 11);
        D_PUSH_LINE(12, 13);

#undef  D_PUSH_LINE

    }

    Abstract_Geometry::generate();

    glCheckError();

}

void    Geometry_Box::bind()
{
    if (!_isInitialized)
        this->generate();

    glBindVertexArray( _VAO_ID );
}

void    Geometry_Box::render()
{
    if (!_isInitialized)
        this->bind();

    glDrawElements( GL_LINES, _indices.size(), GL_UNSIGNED_INT, (void*)0 );
}

