#include "geometry_hud_grid.h"

#include "perlin3d_chunk.h"


void    Geometry_HUD_Grid::setSideSize(float sideSize)
{
    _sideSize = sideSize;
    _isInitialized = false;
}

Geometry_HUD_Grid::Geometry_HUD_Grid( t_Shader_Perlin3D& shader )
    : Abstract_Geometry(shader),
      _sideSize(0)
{
}

Geometry_HUD_Grid::~Geometry_HUD_Grid()
{
    if (_VBO_and_VAO_initialized)
    {
        glDeleteVertexArrays( eVAO_Count, _pGridVertexArrayObject_IDs );
        glDeleteBuffers( eVBO_Count, _pGridVertexBufferObject_IDs );
    }
}

void    Geometry_HUD_Grid::generate()
{

    _gridVertices.clear();
    _gridIndices.clear();


    {

        myGL::Vec3f tmp_color(1,1,1);
        //(void)tmp_color;

#define SIDE                                ( _sideSize * 10.0f )
#define PUSH_GRID_VERTEX(l_X, l_Y, l_Z)     _gridVertices.push_back( t_Vertex( myGL::Vec3f((l_X), (l_Y), (l_Z)), tmp_color ) )

        for (int i = -4; i <= 4; ++i)
        {
            tmp_color = myGL::Vec3f(1,0,0);
            PUSH_GRID_VERTEX(-SIDE * 10, 0, i * SIDE);
            PUSH_GRID_VERTEX(+SIDE * 10, 0, i * SIDE);

            PUSH_GRID_VERTEX(-SIDE * 10, i * SIDE, 0);
            PUSH_GRID_VERTEX(+SIDE * 10, i * SIDE, 0);

            ///

            tmp_color = myGL::Vec3f(0,1,0);
            PUSH_GRID_VERTEX(0, -SIDE * 10, i * SIDE);
            PUSH_GRID_VERTEX(0, +SIDE * 10, i * SIDE);

            PUSH_GRID_VERTEX(i * SIDE, -SIDE * 10, 0);
            PUSH_GRID_VERTEX(i * SIDE, +SIDE * 10, 0);

            ///

            tmp_color = myGL::Vec3f(0,0,1);
            PUSH_GRID_VERTEX(i * SIDE, 0, -SIDE * 10);
            PUSH_GRID_VERTEX(i * SIDE, 0, +SIDE * 10);

            PUSH_GRID_VERTEX(0, i * SIDE, -SIDE * 10);
            PUSH_GRID_VERTEX(0, i * SIDE, +SIDE * 10);
        }

#undef  PUSH_GRID_VERTEX
#undef  SIDE

        for (unsigned int i = 0; i < _gridVertices.size(); ++i)
            _gridIndices.push_back( i );

    }

    ///

    if (!_VBO_and_VAO_initialized)
    {
        _VBO_and_VAO_initialized = true;

        glGenVertexArrays( eVAO_Count, _pGridVertexArrayObject_IDs );
        glGenBuffers( eVBO_Count, _pGridVertexBufferObject_IDs );

        { // GRID VAO

            glBindVertexArray( _pGridVertexArrayObject_IDs[eVAO_Grid] );
            {

                glBindBuffer( GL_ARRAY_BUFFER, _pGridVertexBufferObject_IDs[eVBO_Grid_vertices] );
                {
                    glEnableVertexAttribArray( _shader._location_a_vertex );
                    glVertexAttribPointer( _shader._location_a_vertex, 3, GL_FLOAT, GL_FALSE, sizeof(t_Vertex), (const GLvoid*)0 );

                    glEnableVertexAttribArray( _shader._location_a_color );
                    glVertexAttribPointer( _shader._location_a_color, 3, GL_FLOAT, GL_FALSE, sizeof(t_Vertex), (const GLvoid*)(sizeof(float) * 3) );

                    glEnableVertexAttribArray( _shader._location_a_normal );
                    glVertexAttribPointer( _shader._location_a_normal, 3, GL_FLOAT, GL_FALSE, sizeof(t_Vertex), (const GLvoid*)(sizeof(float) * 6) );
                }

                glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _pGridVertexBufferObject_IDs[eVBO_Grid_indices] );

            }
            glBindVertexArray( 0 );

        } // /GRID VAO
    }

    ///

    { // GRID VBOs

        glBindVertexArray( 0 );

        glBindBuffer( GL_ARRAY_BUFFER, _pGridVertexBufferObject_IDs[eVBO_Grid_vertices] );
        {
            glBufferData( GL_ARRAY_BUFFER, sizeof(t_Vertex) * _gridVertices.size(), &(_gridVertices[0]._coord.x), GL_STATIC_DRAW );
        }
        glBindBuffer( GL_ARRAY_BUFFER, 0 );

        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _pGridVertexBufferObject_IDs[eVBO_Grid_indices] );
        {
            glBufferData( GL_ELEMENT_ARRAY_BUFFER, _gridIndices.size() * sizeof(GLuint), (void*)&(_gridIndices[0]), GL_STATIC_DRAW );
        }
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

    } // /GRID VBOss

    ///

    glCheckError();

    _isInitialized = true;

}

void    Geometry_HUD_Grid::render( const myGL::GL_Matrix& modelviewMatrix, const myGL::Vec3f& camera_pos )
{

    if (!_isInitialized)
        this->generate();

    glCheckError();

    //const myGL::Vec3f&  camera_pos = _FreeFly.getPosition();

#define D_CHUNK ( _sideSize * 5 )

#define D_CHECK_NEG(l_value)        \
    ( ( (l_value) < 0 )             \
    ? ( (l_value) / D_CHUNK - 1 )   \
    : ( (l_value) / D_CHUNK ) )

    myGL::Vec3i i_pos( D_CHECK_NEG( camera_pos.x ),
                       D_CHECK_NEG( camera_pos.y ),
                       D_CHECK_NEG( camera_pos.z ) );

    myGL::Vec3f to_move(i_pos.x, i_pos.y, i_pos.z);
    to_move *= D_CHUNK;

#undef  D_CHUNK
#undef  D_CHECK_NEG

    myGL::GL_Matrix modelMatrix;
    modelMatrix.PreMultTranslate( to_move );

    ///

    myGL::GL_Matrix tmp_modelviewMatrix = modelviewMatrix * modelMatrix;

    ///

    glCheckError();

    glUniformMatrix4fvARB( _shader._location_u_modelviewMatrix, 1, GL_FALSE, tmp_modelviewMatrix.Ptr() );

    glUniform4f( _shader._location_u_mode, 1, 1, 1, 0 );

    glCheckError();

    ///

    glBindVertexArray( _pGridVertexArrayObject_IDs[eVAO_Grid] );
    {
        glDrawElements( GL_LINES, _gridIndices.size(), GL_UNSIGNED_INT, (void*)0 );
    }
    glBindVertexArray( 0 );

    glCheckError();
}

