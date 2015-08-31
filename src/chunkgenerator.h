#ifndef CHUNKGENERATOR_H
#define CHUNKGENERATOR_H


#include "utils/PerlinNoise.hpp"

#include "myGL/GL_Vec3.hpp"


#include <QThread>
#include <QMutex>
#include <QWaitCondition>


class   Perlin3D_Chunk;

class   ChunkGenerator : public QThread
{

private : // Threading utility
    bool    _inUse;
    bool    _abort;

    QMutex          _mutex;
    QWaitCondition  _condition;

public :
    inline bool threadInUse() const { return (_inUse); }

protected :
    void    run();

    ///

private :
    unsigned int   _chunkSize;
    float          _fStepSize;

public :
    unsigned int    getChunkSize() const    { return (_chunkSize); }
    bool            setChunkSize(unsigned int chunkSize);

private :
    float*                      _cache_perlinNoise;
    int*                        _cache_trianglesIndices;

public :
    PerlinNoise                 _PerlinNoise;

private :
    Perlin3D_Chunk*             _pPerlin3D_Chunk;

public :
    explicit ChunkGenerator(QObject *parent = NULL);
    ~ChunkGenerator();

public :
    bool    generate( const myGL::Vec3i& pos,
                      Perlin3D_Chunk* pPerlin3D_Chunk,
                      bool use_thread = true );

private :


    float sample(const float fX, const float fY, const float fZ);

    void  marchingCubes();

    void  getNormal( myGL::Vec3f &rfNormal, const float fX, const float fY, const float fZ );

    void  marchCube( const int iX, const int iY, const int iZ, const float fScale, const float fTv );

};


#endif // CHUNKGENERATOR_H
