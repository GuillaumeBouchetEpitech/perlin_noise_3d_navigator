#include "perlin3dviewerwidget.h"


#include "navigator_globalvalue.h"


#include <limits>


Perlin3DViewerWidget::Perlin3DViewerWidget(QWidget *parent /*= 0*/)
    : FreeFlyCameraWidget(parent),
      _Geometry_HUDGrid(_shader),
      _Geometry_HUD_Frustum(_shader),
      _Geometry_Box(_shader)
{

    Perlin3D_Chunk::initialize( &_shader );

    {
        _Geometry_HUDGrid.setSideSize( Navigator_GlobalValue::pTest->_chunkSize );
        _Geometry_Box.setSideSize( Navigator_GlobalValue::pTest->_chunkSize );
    }

}

Perlin3DViewerWidget::~Perlin3DViewerWidget()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void	Perlin3DViewerWidget::initializeGL()
{

    std::cerr << "FreeFlyCameraWidget::initializeGL" << std::endl;

    FreeFlyCameraWidget::initializeGL();

    ///

    _shader.init();

    ///

    glShadeModel(GL_SMOOTH);

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_LINE_SMOOTH);

    glCheckError();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void    Perlin3DViewerWidget::updatePerlinChunks()
{

    if (!_ChunkGenerator.threadInUse())
    {

        const myGL::Vec3f&    camera_pos = _FreeFly.getPosition();

#define D_CHUNK (float)(_ChunkGenerator.getChunkSize())

#define D_CHECK_NEG(l_value)                            \
    ( ( (l_value) < 0 )                                 \
    ? ( (l_value) / D_CHUNK - 1 )    \
    : ( (l_value) / D_CHUNK ) )

        myGL::Vec3i i_pos( D_CHECK_NEG( camera_pos.x ),
                           D_CHECK_NEG( camera_pos.y ),
                           D_CHECK_NEG( camera_pos.z ) );

#undef  D_CHUNK
#undef  D_CHECK_NEG

        int tmp_dec = Navigator_GlobalValue::pTest->_chunkRange;

        myGL::Vec3i i_min(i_pos.x - tmp_dec, i_pos.y - tmp_dec, i_pos.z - tmp_dec);
        myGL::Vec3i i_max(i_pos.x + tmp_dec, i_pos.y + tmp_dec, i_pos.z + tmp_dec);

        myGL::Vec3i i_inc;

        /**/

        myGL::Vec3i i_inc_best_visible;
        float       length_best_visible = std::numeric_limits<float>::max();

        myGL::Vec3i i_inc_best_not_visible;
        float       length_best_not_visible = std::numeric_limits<float>::max();

        for (i_inc.z = i_min.z; i_inc.z <= i_max.z; ++i_inc.z)
            for (i_inc.y = i_min.y; i_inc.y <= i_max.y; ++i_inc.y)
                for (i_inc.x = i_min.x; i_inc.x <= i_max.x; ++i_inc.x)
                {

                    /// check if this coord got a chunk

                    bool    no_need_to_go_further = false;


                    for (Perlin3D_Chunk* & element : _Perlin3D_Chunks)
                        if ( element->isEnabled() )
                            //                    D_CHUNK_FOREACH(itC)
                            //                            if ((*itC)->isEnabled())
                        {
                            const myGL::Vec3i&  tmp_pos = element->getPosition();

                            if (i_inc == tmp_pos)
                            {
                                no_need_to_go_further = true;
                                break;
                            }
                        }

                    /// if yes => continue

                    if (no_need_to_go_further)
                        continue;

                    /// else
                    ///   check if visible

                    myGL::Vec3f     tmp_pos1;
                    tmp_pos1.x = (float)i_inc.x * (float)Navigator_GlobalValue::pTest->_chunkSize;
                    tmp_pos1.y = (float)i_inc.y * (float)Navigator_GlobalValue::pTest->_chunkSize;
                    tmp_pos1.z = (float)i_inc.z * (float)Navigator_GlobalValue::pTest->_chunkSize;

                    bool    is_visible = _Frustum.cubeInFrustum( tmp_pos1, (float)Navigator_GlobalValue::pTest->_chunkSize );

                    ///   check his length
                    ///   reccord these data for the choice

                    myGL::Vec3f     tmp_pos2;
                    tmp_pos2.x = (float)(i_inc.x - i_pos.x) * (float)Navigator_GlobalValue::pTest->_chunkSize;
                    tmp_pos2.y = (float)(i_inc.y - i_pos.y) * (float)Navigator_GlobalValue::pTest->_chunkSize;
                    tmp_pos2.z = (float)(i_inc.z - i_pos.z) * (float)Navigator_GlobalValue::pTest->_chunkSize;

                    float   tmp_lenght = sqrtf( tmp_pos2.x * tmp_pos2.x +
                                                tmp_pos2.y * tmp_pos2.y +
                                                tmp_pos2.z * tmp_pos2.z );

                    if (is_visible)
                    {
                        if (tmp_lenght < length_best_visible)
                        {
                            i_inc_best_visible = i_inc;
                            length_best_visible = tmp_lenght;
                        }
                    }
                    else
                    {
                        if (tmp_lenght < length_best_not_visible)
                        {
                            i_inc_best_not_visible = i_inc;
                            length_best_not_visible = tmp_lenght;
                        }
                    }

                }


        if ( length_best_visible != std::numeric_limits<float>::max() ||
             length_best_not_visible != std::numeric_limits<float>::max() )
        {

            Perlin3D_Chunk* tmp_Chunk = NULL;


            t_Chunks::iterator  itC = _Perlin3D_Chunks.begin();
            for (; itC != _Perlin3D_Chunks.end(); ++itC)
            {
                const myGL::Vec3i&  tmp_pos = (*itC)->getPosition();

                if ( (*itC)->isDisabled() ||
                     tmp_pos.x < i_min.x || tmp_pos.x > i_max.x ||
                     tmp_pos.y < i_min.y || tmp_pos.y > i_max.y ||
                     tmp_pos.z < i_min.z || tmp_pos.z > i_max.z )
                {
                    break;
                }

            }

            if ( itC == _Perlin3D_Chunks.end() )
            {
                tmp_Chunk = new Perlin3D_Chunk;
                _Perlin3D_Chunks.push_back( tmp_Chunk );
            }
            else
                tmp_Chunk = *itC;



            if ( length_best_visible != std::numeric_limits<float>::max() )
                _ChunkGenerator.generate( i_inc_best_visible, tmp_Chunk );
            else
                _ChunkGenerator.generate( i_inc_best_not_visible, tmp_Chunk );

        }

        /**

        for (i_inc.z = i_min.z; i_inc.z <= i_max.z; ++i_inc.z)
            for (i_inc.y = i_min.y; i_inc.y <= i_max.y; ++i_inc.y)
                for (i_inc.x = i_min.x; i_inc.x <= i_max.x; ++i_inc.x)
                {
                    bool    got_a_chunck = false;

                    D_CHUNK_FOREACH(itC)
//                    for ( t_Chunks::iterator  itC = _Perlin3D_Chunks.begin();
//                          itC != _Perlin3D_Chunks.end();
//                          ++itC )
                        if ((*itC)->isEnabled())
                        {
                            const myGL::Vec3i&  tmp_pos = (*itC)->getPosition();

                            if (i_inc == tmp_pos)
                            {
                                got_a_chunck = true;
                                break;
                            }

                        }

                    if (!got_a_chunck)
                    {

                        t_Chunks::iterator  itC = _Perlin3D_Chunks.begin();
                        for (; itC != _Perlin3D_Chunks.end(); ++itC)
                        {
                            const myGL::Vec3i&  tmp_pos = (*itC)->getPosition();

                            if ( (*itC)->isDisabled() ||
                                 tmp_pos.x < i_min.x || tmp_pos.x > i_max.x ||
                                 tmp_pos.y < i_min.y || tmp_pos.y > i_max.y ||
                                 tmp_pos.z < i_min.z || tmp_pos.z > i_max.z )
                            {
                                _ChunkGenerator.generate( i_inc, *itC );
                                break;
                            }

                        }

                        if ( itC == _Perlin3D_Chunks.end() )
                        {
                            Perlin3D_Chunk* tmp_Chunk = new Perlin3D_Chunk;
                            _Perlin3D_Chunks.push_back( tmp_Chunk );
                            _ChunkGenerator.generate( i_inc, tmp_Chunk );
                        }

                        break;
                    }

                }

        //*/

    }

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void    Perlin3DViewerWidget::renderHUD()
{
    const myGL::Vec3f&  pos = _FreeFly.getPosition();

    //float   side = 7 * (float)_ChunkGenerator.getChunkSize();
    float   side = 2 * Navigator_GlobalValue::pTest->_chunkRange * (float)Navigator_GlobalValue::pTest->_chunkSize;

    int width = this->width();
    int height = this->height();

    float   aspectRatio = (float)width / height;

    myGL::GL_Matrix     Matrix_Proj;
    Matrix_Proj.Make_Ortho( -side * aspectRatio,side * aspectRatio,
                            -side,side,
                            -600,600 );

    glUniformMatrix4fvARB( _shader._location_u_projectionMatrix, 1, GL_FALSE, Matrix_Proj.Ptr() );


    const myGL::Vec3f&  camera_pos = _FreeFly.getPosition();

    int tmp_width = this->width();
    int tmp_height = std::max(this->height(), 1);
    tmp_width = tmp_width / 4 * 3;
    double  aspect_ratio = (double)tmp_width / tmp_height;


    {
        myGL::GL_Matrix     Matrix_View;
        Matrix_View.Make_LookAt( myGL::Vec3f(pos.x, pos.y + 1, pos.z), pos, myGL::Vec3f(0,0,1) );

        glViewport( width / 4 * 3, height / 4 * 3, width / 4, height / 4 );

        renderBoxes( Matrix_View );

        _Geometry_HUDGrid.render( Matrix_View, camera_pos );

        _Geometry_HUD_Frustum.render( Matrix_View, _FreeFly, aspect_ratio );
    }

    {
        myGL::GL_Matrix     Matrix_View;
        Matrix_View.Make_LookAt( myGL::Vec3f(pos.x, pos.y, pos.z + 1), pos, myGL::Vec3f(0,1,0) );

        glViewport( width / 4 * 3, height / 4 * 2, width / 4, height / 4 );

        renderBoxes( Matrix_View );

        _Geometry_HUDGrid.render( Matrix_View, camera_pos );

        _Geometry_HUD_Frustum.render( Matrix_View, _FreeFly, aspect_ratio );
    }

    {
        myGL::GL_Matrix     Matrix_View;
        Matrix_View.Make_LookAt( myGL::Vec3f(pos.x + 1, pos.y, pos.z), pos, myGL::Vec3f(0,0,1) );

        glViewport( width / 4 * 3, height / 4 * 1, width / 4, height / 4 );

        renderBoxes( Matrix_View );

        _Geometry_HUDGrid.render( Matrix_View, camera_pos );

        _Geometry_HUD_Frustum.render( Matrix_View, _FreeFly, aspect_ratio );
    }
}

void    Perlin3DViewerWidget::resizeGL(int width, int height)
{
    //std::cerr << "Perlin3DViewerWidget::resizeGL" << std::endl;

    FreeFlyCameraWidget::resizeGL( width, height );

    _Geometry_HUD_Frustum.regenerate();
}

void    Perlin3DViewerWidget::update()
{
    FreeFlyCameraWidget::update();

    if (Navigator_GlobalValue::pTest->_update_needed)
    {
        Navigator_GlobalValue::pTest->_update_needed = false;

        this->_ChunkGenerator._PerlinNoise.Set( Navigator_GlobalValue::pTest->_octaves,
                                                Navigator_GlobalValue::pTest->_frequency,
                                                Navigator_GlobalValue::pTest->_amplitude,
                                                Navigator_GlobalValue::pTest->_seed );

        if (this->_ChunkGenerator.getChunkSize() != Navigator_GlobalValue::pTest->_chunkSize)
        {
            this->_ChunkGenerator.setChunkSize( Navigator_GlobalValue::pTest->_chunkSize );
            _Geometry_HUDGrid.setSideSize( Navigator_GlobalValue::pTest->_chunkSize );
            _Geometry_Box.setSideSize( Navigator_GlobalValue::pTest->_chunkSize );
        }

        for (Perlin3D_Chunk* & element : _Perlin3D_Chunks)
            element->disable();
    }

    {
        _advance += 1.0f / 30;
        if (_advance > 1.0f)
            _advance = _advance - (int)_advance - 1.0f;
    }

    updatePerlinChunks();
}

void    Perlin3DViewerWidget::paintGL()
{
    int width = this->width();
    int height = this->height();
    glViewport( 0, 0, width / 4 * 3, height );

    ///

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ///

    glUniformMatrix4fvARB( _shader._location_u_modelviewMatrix, 1, GL_FALSE, _viewMatrix.Ptr() );
    glUniformMatrix4fvARB( _shader._location_u_projectionMatrix, 1, GL_FALSE, _projectionMatrix.Ptr() );

    float   pMat3x3[9];
    for (int i = 0; i < 9; ++i) pMat3x3[i] = _viewMatrix( i % 3, i / 3);
    glUniformMatrix3fvARB( _shader._location_u_normalMatrix, 1, GL_FALSE, pMat3x3 );

    /**/
    _shader._properties_light.direction = myGL::Vec3f(1,1,1);
    myGL::normalize( _shader._properties_light.direction );
    myGL::Vec3f     direction;
    for (int i = 0; i < 3; i++)
        (&(direction.x))[i] =
            _viewMatrix.Ptr()[0 + i] * (&(_shader._properties_light.direction.x))[0] +
            _viewMatrix.Ptr()[4 + i] * (&(_shader._properties_light.direction.x))[1] +
            _viewMatrix.Ptr()[8 + i] * (&(_shader._properties_light.direction.x))[2];
    glUniform3fv( _shader._locations_light.directionLocation, 1, &(direction.x) );
    //*/

    { // HULL

        glUniform4f( _shader._location_u_mode, 1, 1, 1, 0 );


        bool    lightEnabled = Navigator_GlobalValue::pTest->_lightEnabled;
        glUniform1i( _shader._location_u_lightEnabled, lightEnabled ? 1 : 0 );


        bool    perturbationEnabled = Navigator_GlobalValue::pTest->_perturbationEnabled;

        if (perturbationEnabled)
        {
            glUniform1f( _shader._location_u_advance, _advance );
            glUniform1i( _shader._location_u_perturbationEnabled, 1 );
        }


        if (Navigator_GlobalValue::pTest->_polyEnabled)
        {

            for (Perlin3D_Chunk* & element : _Perlin3D_Chunks)
                if (element->isVisible( _Frustum ))
                    element->render();

        }



        if (lightEnabled)
            glUniform1i(  _shader._location_u_lightEnabled, 0 );



        glDepthFunc(GL_LEQUAL);

        glUniform4f( _shader._location_u_mode, 0, 0, 0, 1 );

        if (Navigator_GlobalValue::pTest->_lineEnabled)
        {

            for (Perlin3D_Chunk* & element : _Perlin3D_Chunks)
                if (element->isVisible( _Frustum ))
                    element->render_lines();

        }

        if (perturbationEnabled)
            glUniform1i( _shader._location_u_perturbationEnabled, 0 );

        glDepthFunc(GL_LESS);



        glCheckError();



        {

            //            myGL::Vec2f Target(this->width() / 8 * 3, this->height() / 2);
            //            myGL::Vec3f Position;

            //            if (_FreeFly.get3DPoint( Target, Position ))
            //            {

            //                myGL::Vec3f to_move = Position;
            //                to_move.x -= (float)Perlin3D_Chunk::_chunkSize / 2;
            //                to_move.y -= (float)Perlin3D_Chunk::_chunkSize / 2;
            //                to_move.z -= (float)Perlin3D_Chunk::_chunkSize / 2;

            //                myGL::GL_Matrix Matrix_Model;
            //                Matrix_Model.PreMultTranslate( to_move );

            //                /**
            //                myGL::GL_Matrix Matrix_Model2;
            //                //float   ratio = 1.0f / (float)Perlin3D_Chunk::_chunkSize;
            //                //float   ratio = 0.01f;
            //                float   ratio = 2.01f;
            //                Matrix_Model2.PreMultScale( myGL::Vec3f( ratio, ratio, ratio ) );
            //                //*/

            //                ///

            //                myGL::GL_Matrix tmp_modelviewMatrix = _FreeFly.get_ViewMatrix() * Matrix_Model;
            //                //myGL::GL_Matrix tmp_modelviewMatrix = Matrix_Model2 * _FreeFly.get_ViewMatrix() * Matrix_Model;

            //                glUniformMatrix4fvARB( _location_u_modelviewMatrix, 1, GL_FALSE, tmp_modelviewMatrix.Ptr() );

            //                ///

            //                glUniform4f( _location_u_mode, 1, 0, 0, 1 );

            //                glBindVertexArray( _boxVertexArrayObject_id );

            //                glDrawElements( GL_LINES, _boxIndices.size(), GL_UNSIGNED_INT, (void*)0 );

            //                glBindVertexArray( 0 );
            //            }

        }

    } // /HULL

    /**
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //*/

    ///


    glCheckError();

    { // BOX

        glUniformMatrix4fvARB( _shader._location_u_projectionMatrix, 1, GL_FALSE, _projectionMatrix.Ptr() );
        renderBoxes( _viewMatrix );

    } // /BOX

    { // HUD

        glClear(GL_DEPTH_BUFFER_BIT);

        renderHUD();

    } // /HUD

    glFlush();

    glCheckError();
}


void    Perlin3DViewerWidget::renderBoxes( const myGL::GL_Matrix& modelviewMatrix )
{
    const myGL::Vec3f&  camera_pos = _FreeFly.getPosition();

    _Geometry_Box.bind();

    ///

    glUniform4f( _shader._location_u_mode, 0, 1, 0, 1 );
    glUniformMatrix4fvARB( _shader._location_u_modelviewMatrix, 1, GL_FALSE, modelviewMatrix.Ptr() );

    for (Perlin3D_Chunk* & element : _Perlin3D_Chunks)
        if (element->isEnabled())
        {
            const myGL::Vec3i&  chunk_pos = element->getPosition();
            myGL::Vec3f chunk_fpos(chunk_pos.x, chunk_pos.y, chunk_pos.z);

#define D_SIDE  ((float)_ChunkGenerator.getChunkSize())

            chunk_fpos *= D_SIDE;

            if ( camera_pos.x > chunk_fpos.x &&
                 camera_pos.y > chunk_fpos.y &&
                 camera_pos.z > chunk_fpos.z &&
                 camera_pos.x < chunk_fpos.x + D_SIDE &&
                 camera_pos.y < chunk_fpos.y + D_SIDE &&
                 camera_pos.z < chunk_fpos.z + D_SIDE )
                renderBox( modelviewMatrix, *element );
        }

    ///

    glUniform4f( _shader._location_u_mode, 1, 1, 1, 1 );

    for (Perlin3D_Chunk* & element : _Perlin3D_Chunks)
        if ( element->isEnabled() &&
             element->isVisible( _Frustum ) )
            renderBox( modelviewMatrix, *element );

    ///

    glUniform4f( _shader._location_u_mode, 1, 1, 0, 1 );

    for (Perlin3D_Chunk* & element : _Perlin3D_Chunks)
        if ( element->isEnabled() &&
             !element->isVisible( _Frustum ) )
            renderBox( modelviewMatrix, *element );

    ///

    glUniform4f( _shader._location_u_mode, 1, 0, 0, 1 );

    for (Perlin3D_Chunk* & element : _Perlin3D_Chunks)
        if ( element->isDisabled() )
            renderBox( modelviewMatrix, *element );

    ///

    _Geometry_Box.unbind();

    glCheckError();
}

void    Perlin3DViewerWidget::renderBox( const myGL::GL_Matrix& modelviewMatrix, const Perlin3D_Chunk& Chunk )
{
    const myGL::Vec3i&  pos = Chunk.getPosition();

    myGL::Vec3f to_move(pos.x, pos.y, pos.z);
    to_move *= (float)_ChunkGenerator.getChunkSize();

    myGL::GL_Matrix Matrix_Model;
    Matrix_Model.PreMultTranslate( to_move );

    ///

    myGL::GL_Matrix tmp_modelviewMatrix = modelviewMatrix * Matrix_Model;

    glUniformMatrix4fvARB( _shader._location_u_modelviewMatrix, 1, GL_FALSE, tmp_modelviewMatrix.Ptr() );

    ///

    _Geometry_Box.render();

}
