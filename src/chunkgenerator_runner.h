
#ifndef CHUNKGENERATOR_RUNNER_H
#define CHUNKGENERATOR_RUNNER_H


#include "generation/PerlinNoise.hpp"
#include "generation/MarchingCube.hpp"

#include "myGL/GL_Vec3.hpp"

#include <QRunnable>



class	ChunkGenerator;
class   Perlin3D_Chunk;

class   Runner : public QRunnable
{
private:
    ChunkGenerator& _ChunkGenerator;
    MarchingCube    _marchingCube;

public:
    Runner(ChunkGenerator& cg, PerlinNoise& p);

    void set( unsigned int chunk_size,
                const myGL::Vec3i& pos,
                Perlin3D_Chunk* pPerlin3D_Chunk );

    virtual void run();
};




#endif // CHUNKGENERATOR_RUNNER_H
