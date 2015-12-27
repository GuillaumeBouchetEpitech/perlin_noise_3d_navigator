
#include "abstract_geometry.h"


Abstract_Geometry::Abstract_Geometry( t_Shader_Perlin3D& shader )
    : _shader(shader),
      _isInitialized(false),
      _VBO_and_VAO_initialized(false)
{
}

Abstract_Geometry::~Abstract_Geometry()
{
    if (_VBO_and_VAO_initialized)
    {
        glDeleteVertexArrays( 1, &_VAO_ID );
        glDeleteBuffers( eVBO_count, _pVBO_IDs );
    }
}

void	Abstract_Geometry::generate()
{
    if (!_VBO_and_VAO_initialized)
    {
        _VBO_and_VAO_initialized = true;

        glGenVertexArrays( 1, &_VAO_ID );
        glGenBuffers( 2, _pVBO_IDs );

        { /// BOX VAO

            glBindVertexArray( _VAO_ID );

            ///

            glBindBuffer( GL_ARRAY_BUFFER, _pVBO_IDs[eVBO_vertices] );
            {

                glEnableVertexAttribArray( _shader._location_a_vertex );
                glVertexAttribPointer( _shader._location_a_vertex, 3, GL_FLOAT, GL_FALSE, sizeof(t_Vertex), (const GLvoid*)0 );

                glEnableVertexAttribArray( _shader._location_a_color );
                glVertexAttribPointer( _shader._location_a_color, 3, GL_FLOAT, GL_FALSE, sizeof(t_Vertex), (const GLvoid*)(sizeof(float) * 3) );

                glEnableVertexAttribArray( _shader._location_a_normal );
                glVertexAttribPointer( _shader._location_a_normal, 3, GL_FLOAT, GL_FALSE, sizeof(t_Vertex), (const GLvoid*)(sizeof(float) * 6) );

            }

            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _pVBO_IDs[eVBO_indices] );

        } /// /BOX VAO

    }

    ///


    { // BOX VBOs

        glBindVertexArray( 0 );

        glBindBuffer( GL_ARRAY_BUFFER, _pVBO_IDs[eVBO_vertices] );
        {
            glBufferData( GL_ARRAY_BUFFER, sizeof(t_Vertex) * _vertices.size(), &(_vertices[0]._coord.x), GL_STATIC_DRAW );
        }
        glBindBuffer( GL_ARRAY_BUFFER, 0 );

        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _pVBO_IDs[eVBO_indices] );
        {
            glBufferData( GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(GLuint), (void*)&(_indices[0]), GL_STATIC_DRAW );
        }
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

    } // BOX VBOs

    ///

    glCheckError();
}
