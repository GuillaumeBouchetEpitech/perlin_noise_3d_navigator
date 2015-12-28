#ifndef CHUNKGENERATOR_H
#define CHUNKGENERATOR_H


#include "generation/PerlinNoise.hpp"
#include "generation/MarchingCube.hpp"


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

    MarchingCube    _marchingCube; 

protected :
    void    run();

public :
    explicit ChunkGenerator(QObject *parent = NULL);
    ~ChunkGenerator();

public :
    bool    generate( const myGL::Vec3i& pos,
                      Perlin3D_Chunk* pPerlin3D_Chunk,
                      bool use_thread = true );
};


#endif // CHUNKGENERATOR_H
