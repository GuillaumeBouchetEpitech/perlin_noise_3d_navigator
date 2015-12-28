#include "perlin3d_chunk.h"

#include "chunkgenerator.h"

#include "widgets/perlin3dviewerwidget.h"


#include <QElapsedTimer>

#include <iostream>
#include <iomanip>



t_Shader_Perlin3D*  Perlin3D_Chunk::_pShader = NULL;


void  Perlin3D_Chunk::initialize( t_Shader_Perlin3D* pShader )
{
    _pShader = pShader;
}

Perlin3D_Chunk::Perlin3D_Chunk()
    : _enabled(false),
      _VBO_and_VAO_initialized(false),
      _is_computed(false)
{
}

Perlin3D_Chunk::~Perlin3D_Chunk()
{
    if (_VBO_and_VAO_initialized)
    {
        glDeleteVertexArrays( eVAO_Count, _pChunkVertexArrayObject_IDs );
        glDeleteBuffers( eVBO_Count, _pChunkVertexBufferObject_IDs );
    }
}

///////////////////////////////////////////////////////////////////////////

void    Perlin3D_Chunk::render()
{

    if ( _Indices.empty() )
        return;

    if (!_is_computed)
        computeBuffers();

    ///

    glBindVertexArray( _pChunkVertexArrayObject_IDs[eVAO_Perlin3dHull] );

    // glDrawElements( GL_TRIANGLES, _Indices.size(), GL_UNSIGNED_INT, (void*)0 );
    glDrawArrays( GL_TRIANGLES, 0, _Vertices.size() );

    glBindVertexArray( 0 );
}


void    Perlin3D_Chunk::render_lines()
{

    if ( _Indices_lines.empty() )
        return;

    if (!_is_computed)
        computeBuffers();

    ///


    glCheckError();

    glBindVertexArray( _pChunkVertexArrayObject_IDs[eVAO_Perlin3dLines] );

    glDrawElements( GL_LINES, _Indices_lines.size(), GL_UNSIGNED_INT, (void*)0 );
    // glDrawArrays( GL_LINES, 0, _Indices_lines.size() );

    glBindVertexArray( 0 );
}


bool    Perlin3D_Chunk::isVisible( const myGL::GL_FrustumCulling& Frustum )
{
    return ( Frustum.cubeInFrustum( (float)_pos.x * _sideSize,
                                    (float)_pos.y * _sideSize,
                                    (float)_pos.z * _sideSize,
                                    _sideSize ) );
}


void    Perlin3D_Chunk::computeBuffers()
{

    if (!_VBO_and_VAO_initialized)
    {
        _VBO_and_VAO_initialized = true;

        glCheckError();

        glGenVertexArrays( eVAO_Count, _pChunkVertexArrayObject_IDs );
        glGenBuffers( eVBO_Count, _pChunkVertexBufferObject_IDs );

        glCheckError();

        ///

        { // CHUNK VAOs

            { // VAO HULL
                glBindVertexArray( _pChunkVertexArrayObject_IDs[eVAO_Perlin3dHull] );
                {

                    glBindBuffer( GL_ARRAY_BUFFER, _pChunkVertexBufferObject_IDs[eVBO_Perlin3dHull_vertices] );
                    {
                        glEnableVertexAttribArray( _pShader->_location_a_vertex );
                        glVertexAttribPointer( _pShader->_location_a_vertex, 3, GL_FLOAT, GL_FALSE, sizeof(t_Vertex), (const GLvoid*)0 );

                        glEnableVertexAttribArray( _pShader->_location_a_color );
                        glVertexAttribPointer( _pShader->_location_a_color, 3, GL_FLOAT, GL_FALSE, sizeof(t_Vertex), (const GLvoid*)(sizeof(float) * 3) );

                        glEnableVertexAttribArray( _pShader->_location_a_normal );
                        glVertexAttribPointer( _pShader->_location_a_normal, 3, GL_FLOAT, GL_FALSE, sizeof(t_Vertex), (const GLvoid*)(sizeof(float) * 6) );
                    }

                    // glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _pChunkVertexBufferObject_IDs[eVBO_Perlin3dHull_indices] );

                }
                glBindVertexArray( 0 );
            } // /VAO HULL

            glCheckError();

            { // VAO LINES
                glBindVertexArray( _pChunkVertexArrayObject_IDs[eVAO_Perlin3dLines] );
                {

                    glBindBuffer( GL_ARRAY_BUFFER, _pChunkVertexBufferObject_IDs[eVBO_Perlin3dHull_vertices] );
                    {
                        glEnableVertexAttribArray( _pShader->_location_a_vertex );
                        glVertexAttribPointer( _pShader->_location_a_vertex, 3, GL_FLOAT, GL_FALSE, sizeof(t_Vertex), (const GLvoid*)0 );

                        glEnableVertexAttribArray( _pShader->_location_a_color );
                        glVertexAttribPointer( _pShader->_location_a_color, 3, GL_FLOAT, GL_FALSE, sizeof(t_Vertex), (const GLvoid*)(sizeof(float) * 3) );

                        glEnableVertexAttribArray( _pShader->_location_a_normal );
                        glVertexAttribPointer( _pShader->_location_a_normal, 3, GL_FLOAT, GL_FALSE, sizeof(t_Vertex), (const GLvoid*)(sizeof(float) * 6) );
                    }

                    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _pChunkVertexBufferObject_IDs[eVBO_Perlin3dLines_indices] );

                }
                glBindVertexArray( 0 );
            } // /VAO LINES

        } // /CHUNK VAOs

        glCheckError();

    } // if (!_VBO_and_VAO_initialized)

    ///

    glCheckError();

    ///

    { // /CHUNK VBOs

        glBindVertexArray( 0 );

        { // HULL VBO
            glBindBuffer( GL_ARRAY_BUFFER, _pChunkVertexBufferObject_IDs[eVBO_Perlin3dHull_vertices] );
            {
                glBufferData( GL_ARRAY_BUFFER, sizeof(t_Vertex) * _Vertices.size(), &(_Vertices[0]._coord.x), GL_STATIC_DRAW );
            }
            glBindBuffer( GL_ARRAY_BUFFER, 0 );

            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _pChunkVertexBufferObject_IDs[eVBO_Perlin3dHull_indices] );
            {
                glBufferData( GL_ELEMENT_ARRAY_BUFFER, _Indices.size() * sizeof(GLuint), (void*)&(_Indices[0]), GL_STATIC_DRAW );
            }
            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
        } // HULL /VBO

        { // LINES VBO
            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _pChunkVertexBufferObject_IDs[eVBO_Perlin3dLines_indices] );
            {
                glBufferData( GL_ELEMENT_ARRAY_BUFFER, _Indices_lines.size() * sizeof(GLuint), (void*)&(_Indices_lines[0]), GL_STATIC_DRAW );
            }
            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
        } // /LINES VBO

    } // /CHUNK VBOs

    ///

    glCheckError();

    _is_computed = true;
}







