
#include "chunkgenerator.h"

#include "perlin3d_chunk.h"




void    ChunkGenerator::run()
{
    while (!_abort)
    {
        _condition.wait( &_mutex );

        if (_marchingCube._pPerlin3D_Chunk)
        {
            _marchingCube.execute();

            // _marchingCube._pPerlin3D_Chunk->_is_computed = false;
            // _marchingCube._pPerlin3D_Chunk->_enabled = true;
        }

        _inUse = false;
    }
}




ChunkGenerator::ChunkGenerator(QObject* parent)
    :
      QThread(parent),
      _inUse(false),
      _abort(false)
{
    //this->start( LowPriority );
    this->start( QThread::HighestPriority );
}

ChunkGenerator::~ChunkGenerator()
{
    _mutex.lock();
    {
        _abort = true;
        //_pChunk = NULL;
        _condition.wakeOne();
    }
    _mutex.unlock();

    this->wait();
    _inUse = false;
}



bool    ChunkGenerator::generate( const myGL::Vec3i& pos,
                  Perlin3D_Chunk* pPerlin3D_Chunk,
                  bool use_thread /*= true*/ )
{
    if (_inUse)
        return (false);
    _inUse = true;

    ///

    _marchingCube.prepare(pos, pPerlin3D_Chunk);

    if (use_thread)
    {
        QMutexLocker    locker( &_mutex );
        _condition.wakeOne();
    }
    else
    {
        _marchingCube.execute();

        _inUse = false;
    }

    return (true);
}


