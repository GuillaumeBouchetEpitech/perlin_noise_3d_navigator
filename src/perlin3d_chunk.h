#ifndef PERLIN3D_CHUNK_H
#define PERLIN3D_CHUNK_H


#include "utils/PerlinNoise.hpp"


#include "glheader.h"

#include "myGL/GL_FreeFlyController.hpp"

#include "geometry/t_vertex.h"


//#include <vector>

//#include <QThread>





struct  t_Shader_Perlin3D;

class   ChunkGenerator;

class   Perlin3D_Chunk
{
private :
    friend class    ChunkGenerator;

private :
    static t_Shader_Perlin3D*   _pShader;
public:
    static void  initialize( t_Shader_Perlin3D* pShader );

    ///////////////////////////////

private :
    myGL::Vec3i _pos;
    float       _sideSize;

    bool        _enabled;

    bool    _VBO_and_VAO_initialized;

private :
    enum {
        eVAO_Perlin3dHull = 0,
        eVAO_Perlin3dLines,
        eVAO_Count
    };

    enum {
        eVBO_Perlin3dHull_vertices = 0,
        eVBO_Perlin3dHull_indices,
        eVBO_Perlin3dLines_indices,
        eVBO_Count
    };

private :
    GLuint  _pChunkVertexArrayObject_IDs[eVAO_Count];
    GLuint  _pChunkVertexBufferObject_IDs[eVBO_Count];

private :
    t_Vertices  _Vertices;
    t_Indices   _Indices;
    t_Indices   _Indices_lines;

public :
    Perlin3D_Chunk();
    ~Perlin3D_Chunk();

private :

    bool    _is_computed;
    void    computeBuffers();

public :

    void    render();
    void    render_lines();

public :

    bool    isVisible( const myGL::GL_FrustumCulling& Frustum );



    inline const myGL::Vec3i&   getPosition() const { return (_pos); }

    //inline void enable()    { _enabled = true; }
    inline void disable()   { _enabled = false; }

    inline bool isEnabled() const   { return (_enabled); }
    inline bool isDisabled() const  { return (!_enabled); }


    /**
private :
    GLfloat sample(const GLfloat fX, const GLfloat fY, const GLfloat fZ);
    GLvoid  marchingCubes();
    GLvoid  getNormal( myGL::Vec3f &rfNormal, const GLfloat fX, const GLfloat fY, const GLfloat fZ );
    GLvoid  marchCube( const GLint iX, const GLint iY, const GLint iZ, const GLfloat fScale, const GLfloat fTv );
    //*/

};




#endif // PERLIN3D_CHUNK_H
