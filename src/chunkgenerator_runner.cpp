

#include "chunkgenerator_runner.h"

#include "chunkgenerator.h"

#include "perlin3d_chunk.h"


Runner::Runner(ChunkGenerator& cg, PerlinNoise& p)
    :   _ChunkGenerator(cg)
{
    setAutoDelete(false);
    _marchingCube._PerlinNoise = &p;
}

void Runner::set( unsigned int chunk_size,
            const myGL::Vec3i& pos,
            Perlin3D_Chunk* pPerlin3D_Chunk )
{
    _marchingCube.setChunkSize(chunk_size);
    _marchingCube.prepare(pos, pPerlin3D_Chunk);
}

void Runner::run()
{
    if (_marchingCube._pPerlin3D_Chunk)
        _marchingCube.execute();

    _ChunkGenerator.makeAvailable(this);
}

