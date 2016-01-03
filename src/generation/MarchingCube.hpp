
#ifndef MARCHINGCUBE_HPP
#define MARCHINGCUBE_HPP


#include "generation/PerlinNoise.hpp"

#include "myGL/GL_Vec3.hpp"


class   Perlin3D_Chunk;

class   MarchingCube
{
private :
    unsigned int   _chunkSize;
    float          _fStepSize;

public :
    unsigned int    getChunkSize() const    { return (_chunkSize); }
    void            setChunkSize(unsigned int chunkSize);

public : // TODO -> this is ugly
    PerlinNoise*    _PerlinNoise;
    Perlin3D_Chunk* _pPerlin3D_Chunk;

public :
    MarchingCube();
    ~MarchingCube();

public :
    void    prepare( const myGL::Vec3i& pos, Perlin3D_Chunk* pPerlin3D_Chunk );
    void    execute();

public : // TODO -> this is ugly
    float sample(const float fX, const float fY, const float fZ);

    void  marchingCubes();

    void  getNormal( myGL::Vec3f &rfNormal, const float fX, const float fY, const float fZ );

    void  marchCube( const int iX, const int iY, const int iZ, const float fScale, const float fTv );

};


#endif // CHUNKGENERATOR_H
