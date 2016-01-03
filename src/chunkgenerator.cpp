
#include "chunkgenerator.h"

#include "chunkgenerator_runner.h"

#include "perlin3d_chunk.h"



#include <QThreadPool>

#include <iostream>



ChunkGenerator::ChunkGenerator()
{
    {
        int     octaves = 1;
        float   freq = 1.0f;
        float   amp = 1.0f;
        int     seed = 0;

        _PerlinNoise.Set( octaves, freq, amp, seed );
    }

    //

    int count_max = QThread::idealThreadCount() / 2;
    if (count_max <= 0)
        count_max = 1;

    QThreadPool::globalInstance()->setMaxThreadCount(count_max);

    std::cout << "count_max=" << count_max << std::endl;

    //

    _arrFree.reserve(count_max);
    for (int i = 0; i < count_max; ++i)
        _arrFree.push_back( new Runner(*this, _PerlinNoise) );
}

ChunkGenerator::~ChunkGenerator()
{
    QThreadPool::globalInstance()->waitForDone();

    for (unsigned int i = 0; i < _arrFree.size(); ++i)
        delete _arrFree[i];
}



bool    ChunkGenerator::generate( const myGL::Vec3i& pos, Perlin3D_Chunk* pc )
{
    if (_arrFree.empty())
        return (false);

    std::cout << "generate=" << pos.x << "/" << pos.y << "/" << pos.z << std::endl;
    std::cout << "_arrFree=" << _arrFree.size() << " (-1)" << std::endl;
    std::cout << "active=" << QThreadPool::globalInstance()->activeThreadCount() << std::endl;


    Runner* tmpRunner = _arrFree.back();
    _arrFree.pop_back();
    // _arrBusy.push_back(tmpRunner);

    tmpRunner->set(_chunkSize, pos, pc );

    QThreadPool::globalInstance()->start( tmpRunner );

    return (true);
}


void    ChunkGenerator::makeAvailable(Runner* r)
{
    _arrFree.push_back(r);

    std::cout << "_arrFree=" << _arrFree.size() << " (+1)" << std::endl;
}
