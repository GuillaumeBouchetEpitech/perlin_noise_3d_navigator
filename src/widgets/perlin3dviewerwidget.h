#ifndef PERLIN3DVIEWERWIDGET_H
#define PERLIN3DVIEWERWIDGET_H


#include "FreeFlyCameraWidget.hpp"


#include "chunkgenerator.h"

#include "perlin3d_chunk.h"

#include "t_shader_perlin3d.h"


#include "geometry/geometry_hud_grid.h"
#include "geometry/geometry_hud_frustum.h"
#include "geometry/geometry_box.h"


#include <vector>



class   Perlin3DViewerWidget : public FreeFlyCameraWidget
{
public:
    Perlin3DViewerWidget(QWidget *parent = 0);
    virtual ~Perlin3DViewerWidget();

private :

    PerlinNoise _PerlinNoise;

    ChunkGenerator  _ChunkGenerator;

    typedef std::vector< Perlin3D_Chunk* >  t_Chunks;

    t_Chunks   _Perlin3D_Chunks;

public :
    t_Shader_Perlin3D   _shader;

    float   _advance;

private :
    Geometry_HUD_Grid       _Geometry_HUDGrid;
    Geometry_HUD_Frustum    _Geometry_HUD_Frustum;
    Geometry_Box            _Geometry_Box;

private :
    void    updatePerlinChunks();

private :
    void    renderHUD();
    void    renderBoxes( const myGL::GL_Matrix& modelviewMatrix );
    void    renderBox( const myGL::GL_Matrix& modelviewMatrix, const Perlin3D_Chunk& Chunk );

public :
    virtual void	initializeGL();
    virtual void    update();
    virtual void	resizeGL(int width, int height);
    virtual void	paintGL();

};

#endif // PERLIN3DVIEWERWIDGET_H
