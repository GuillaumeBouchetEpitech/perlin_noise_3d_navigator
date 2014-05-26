#include "geometry_hud_frustum.h"


Geometry_HUD_Frustum::Geometry_HUD_Frustum( t_Shader_Perlin3D& shader )
    : Abstract_Geometry( shader )
{
}

Geometry_HUD_Frustum::~Geometry_HUD_Frustum()
{
    if (_VBO_and_VAO_initialized)
    {
        glDeleteVertexArrays( eVAO_Count, _pFrustumVertexArrayObject_IDs );
        glDeleteBuffers( eVBO_Count, _pFrustumVertexBufferObject_IDs );
    }
}



void    Geometry_HUD_Frustum::generate( double aspect_ratio )
{

    std::cerr << "Geometry_HUD_Frustum::generate : " << aspect_ratio << std::endl;

    _frustumVertices.clear();
    _frustumIndices.clear();

    {

        {
            float	left, right, bottom, top;

#define	D_PERSPECTIVE(fovY, aspect, zNear, zFar)	\
            {                                               \
    const GLdouble pi = 3.1415926f;             \
    GLdouble fW, fH;                            \
    \
    fH = tan( fovY / 360.0 * pi ) * zNear;		\
    fW = fH * aspect;                           \
    \
    left = -fW;                                 \
    right = +fW;                                \
    \
    top = +fH;                                  \
    bottom = -fH;                               \
        }

            /**
            int width = this->width();
            int height = this->height();
            width = width / 4 * 3;
            //*/
            //double  aspect_ratio = (double)width / height;

            double  fovy = 70.0;
            double  nearval = 1.0;
            double  farval = 100.0;

            D_PERSPECTIVE(fovy, aspect_ratio, nearval, farval);

#undef	D_PERSPECTIVE

            myGL::Vec3f tmp_color(1,1,1);

            _frustumVertices.push_back( t_Vertex( myGL::Vec3f(nearval, left,  top), tmp_color ) );
            _frustumVertices.push_back( t_Vertex( myGL::Vec3f(nearval, right, top), tmp_color ) );
            _frustumVertices.push_back( t_Vertex( myGL::Vec3f(nearval, left,  bottom), tmp_color ) );
            _frustumVertices.push_back( t_Vertex( myGL::Vec3f(nearval, right, bottom), tmp_color ) );

            //            float	half_y = farval * sinf(fovy * 3.14f / 180.0f);
            //            float	half_z = half_y / aspect_ratio;
            float	half_z = farval * sinf(fovy * 3.14f / 180.0f);
            float	half_y = half_z * aspect_ratio;

            _frustumVertices.push_back( t_Vertex( myGL::Vec3f( farval, -half_y, +half_z ), tmp_color ) );
            _frustumVertices.push_back( t_Vertex( myGL::Vec3f( farval, +half_y, +half_z ), tmp_color ) );
            _frustumVertices.push_back( t_Vertex( myGL::Vec3f( farval, -half_y, -half_z ), tmp_color ) );
            _frustumVertices.push_back( t_Vertex( myGL::Vec3f( farval, +half_y, -half_z ), tmp_color ) );
        }

#define D_PUSH_LINE(l_index1, l_index2)     \
    _frustumIndices.push_back( l_index1 );  \
    _frustumIndices.push_back( l_index2 );

        D_PUSH_LINE(0, 1);
        D_PUSH_LINE(1, 3);
        D_PUSH_LINE(3, 2);
        D_PUSH_LINE(2, 0);

        D_PUSH_LINE(0, 4);
        D_PUSH_LINE(1, 5);
        D_PUSH_LINE(2, 6);
        D_PUSH_LINE(3, 7);

        D_PUSH_LINE(4, 5);
        D_PUSH_LINE(5, 7);
        D_PUSH_LINE(7, 6);
        D_PUSH_LINE(6, 4);

#undef  D_PUSH_LINE

        /**
        unsigned int	indices2[] = {
            0,1,3,2, 0,1,5,4, 0,2,6,4,
            4,5,7,6, 2,3,7,6, 1,3,7,5
        };
        //*/

    }

    ///

    if (!_VBO_and_VAO_initialized)
    {
        _VBO_and_VAO_initialized = true;

        glGenVertexArrays( eVAO_Count, _pFrustumVertexArrayObject_IDs );
        glGenBuffers( eVBO_Count, _pFrustumVertexBufferObject_IDs );

        { // FRUSTUM VAO

            glBindVertexArray( _pFrustumVertexArrayObject_IDs[eVAO_Frustum] );
            {

                glBindBuffer( GL_ARRAY_BUFFER, _pFrustumVertexBufferObject_IDs[eVBO_Frustum_vertices] );
                {
                    glEnableVertexAttribArray( _shader._location_a_vertex );
                    glVertexAttribPointer( _shader._location_a_vertex, 3, GL_FLOAT, GL_FALSE, sizeof(t_Vertex), (const GLvoid*)0 );

                    glEnableVertexAttribArray( _shader._location_a_color );
                    glVertexAttribPointer( _shader._location_a_color, 3, GL_FLOAT, GL_FALSE, sizeof(t_Vertex), (const GLvoid*)(sizeof(float) * 3) );

                    glEnableVertexAttribArray( _shader._location_a_normal );
                    glVertexAttribPointer( _shader._location_a_normal, 3, GL_FLOAT, GL_FALSE, sizeof(t_Vertex), (const GLvoid*)(sizeof(float) * 6) );
                }

                glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _pFrustumVertexBufferObject_IDs[eVBO_Frustum_indices] );

            }
            glBindVertexArray( 0 );

        } // /FRUSTUM VAO

    }

    ///

    { // FRUSTUM VBOs

        glBindVertexArray( 0 );

        glBindBuffer( GL_ARRAY_BUFFER, _pFrustumVertexBufferObject_IDs[eVBO_Frustum_vertices] );
        {
            glBufferData( GL_ARRAY_BUFFER, sizeof(t_Vertex) * _frustumVertices.size(), &(_frustumVertices[0]._coord.x), GL_STATIC_DRAW );
        }
        glBindBuffer( GL_ARRAY_BUFFER, 0 );

        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _pFrustumVertexBufferObject_IDs[eVBO_Frustum_indices] );
        {
            glBufferData( GL_ELEMENT_ARRAY_BUFFER, _frustumIndices.size() * sizeof(GLuint), (void*)&(_frustumIndices[0]), GL_STATIC_DRAW );
        }
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

    } // /FRUSTUM VBOs

    ///

    glCheckError();

    _isInitialized = true;
}

void    Geometry_HUD_Frustum::render( const myGL::GL_Matrix& modelviewMatrix,
                                      const myGL::GL_FreeFlyController& FreeFly,
                                      double aspect_ratio )
{

    if (!_isInitialized)
        this->generate(aspect_ratio);



    ////


    float	theta = 0;
    float	phi = 0;

    {
        myGL::Vec3f eye = FreeFly.getPosition();
        myGL::Vec3f target = FreeFly.getTarget();

        myGL::Vec3f	diff;
        diff.x = target.x - eye.x;
        diff.y = target.y - eye.y;
        diff.z = target.z - eye.z;
        theta = atan2f(diff.y, diff.x) * 180.0f / 3.14f;

        myGL::Vec2f	vec;
        vec.x = sqrtf( diff.x * diff.x + diff.y * diff.y );
        vec.y = -diff.z;
        phi = atan2f(vec.y, vec.x) * 180.0f / 3.14f;
    }

    myGL::GL_Matrix modelMatrix;
    modelMatrix.PreMultTranslate( FreeFly.getPosition() );
    modelMatrix.PreMultRotate( theta, 0,0,1 );
    modelMatrix.PreMultRotate( phi, 0,1,0 );


    ////

    ///

    myGL::GL_Matrix tmp_modelviewMatrix = modelviewMatrix * modelMatrix;

    ///

    glCheckError();

    glUniformMatrix4fvARB( _shader._location_u_modelviewMatrix, 1, GL_FALSE, tmp_modelviewMatrix.Ptr() );

    //glUniform4f( _shader._location_u_mode, 1, 1, 1, 0 );
    glUniform4f( _shader._location_u_mode, 1, 1, 1, 1 );

    glCheckError();

    ///

    glBindVertexArray( _pFrustumVertexArrayObject_IDs[eVAO_Frustum] );

    glCheckError();

    {
        glDrawElements( GL_LINES, _frustumIndices.size(), GL_UNSIGNED_INT, (void*)0 );

        glCheckError();
    }
    glBindVertexArray( 0 );

    glCheckError();
}






