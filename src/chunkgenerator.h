#ifndef CHUNKGENERATOR_H
#define CHUNKGENERATOR_H


#include "generation/PerlinNoise.hpp"
#include "generation/MarchingCube.hpp"


#include <iostream>
#include <vector>


class   Perlin3D_Chunk;
class   Runner;



class   ChunkGenerator
{
    friend Runner;

private : // Threading utility

    std::vector<Runner*>    _arrayAvailable;

    PerlinNoise     _PerlinNoise;

public :
    inline bool threadAvailable() const { return (_arrayAvailable.empty()); }

public :
    ChunkGenerator();
    ~ChunkGenerator();

    inline void            setNoise(int octaves, float freq, float amp, int seed) {
        _PerlinNoise.Set( octaves, freq, amp, seed );
    }

public :
    bool    generate( const myGL::Vec3i& pos, Perlin3D_Chunk* pc);

private:
    // this is how the Runner tell the chunkgenerator he's released
    void    makeAvailable(Runner*);

private :
    unsigned int    _chunkSize;
public :
    inline unsigned int    getChunkSize() const    { return (_chunkSize); }
    inline void            setChunkSize(unsigned int c){ _chunkSize = c; }

};


#endif // CHUNKGENERATOR_H
