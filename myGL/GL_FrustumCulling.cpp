

#include "GL_FrustumCulling.hpp"

#include "GL_Vec2.hpp"

//#include "GL_Header.hpp"

#include "GL_Math.hpp"


namespace	myGL
{

void    GL_FrustumCulling::normalizePlane(e_FrustumSide side)
{
    float	magnitude = myGL::fast_sqrt( _Frustum[side][eA] * _Frustum[side][eA] +
                                         _Frustum[side][eB] * _Frustum[side][eB] +
                                         _Frustum[side][eC] * _Frustum[side][eC] );

    _Frustum[side][eA] /= magnitude;
    _Frustum[side][eB] /= magnitude;
    _Frustum[side][eC] /= magnitude;
    _Frustum[side][eD] /= magnitude;
}

void	GL_FrustumCulling::calculateFrustum( const float* proj, const float* modl )
{
    float   clip[16];

#define	D_SET_CLIP(X)							\
    clip[X * 4 + 0] = modl[X * 4]*proj[ 0] + modl[X * 4 + 1]*proj[ 4] + modl[X * 4 + 2]*proj[ 8] + modl[X * 4 + 3]*proj[12]; \
    clip[X * 4 + 1] = modl[X * 4]*proj[ 1] + modl[X * 4 + 1]*proj[ 5] + modl[X * 4 + 2]*proj[ 9] + modl[X * 4 + 3]*proj[13]; \
    clip[X * 4 + 2] = modl[X * 4]*proj[ 2] + modl[X * 4 + 1]*proj[ 6] + modl[X * 4 + 2]*proj[10] + modl[X * 4 + 3]*proj[14]; \
    clip[X * 4 + 3] = modl[X * 4]*proj[ 3] + modl[X * 4 + 1]*proj[ 7] + modl[X * 4 + 2]*proj[11] + modl[X * 4 + 3]*proj[15];

    D_SET_CLIP(0);
    D_SET_CLIP(1);
    D_SET_CLIP(2);
    D_SET_CLIP(3);

#undef	D_SET_CLIP

    // clip[ 0] = modl[ 0] * proj[ 0] + modl[ 1] * proj[ 4] + modl[ 2] * proj[ 8] + modl[ 3] * proj[12];
    // clip[ 1] = modl[ 0] * proj[ 1] + modl[ 1] * proj[ 5] + modl[ 2] * proj[ 9] + modl[ 3] * proj[13];
    // clip[ 2] = modl[ 0] * proj[ 2] + modl[ 1] * proj[ 6] + modl[ 2] * proj[10] + modl[ 3] * proj[14];
    // clip[ 3] = modl[ 0] * proj[ 3] + modl[ 1] * proj[ 7] + modl[ 2] * proj[11] + modl[ 3] * proj[15];

    // clip[ 4] = modl[ 4] * proj[ 0] + modl[ 5] * proj[ 4] + modl[ 6] * proj[ 8] + modl[ 7] * proj[12];
    // clip[ 5] = modl[ 4] * proj[ 1] + modl[ 5] * proj[ 5] + modl[ 6] * proj[ 9] + modl[ 7] * proj[13];
    // clip[ 6] = modl[ 4] * proj[ 2] + modl[ 5] * proj[ 6] + modl[ 6] * proj[10] + modl[ 7] * proj[14];
    // clip[ 7] = modl[ 4] * proj[ 3] + modl[ 5] * proj[ 7] + modl[ 6] * proj[11] + modl[ 7] * proj[15];

    // clip[ 8] = modl[ 8] * proj[ 0] + modl[ 9] * proj[ 4] + modl[10] * proj[ 8] + modl[11] * proj[12];
    // clip[ 9] = modl[ 8] * proj[ 1] + modl[ 9] * proj[ 5] + modl[10] * proj[ 9] + modl[11] * proj[13];
    // clip[10] = modl[ 8] * proj[ 2] + modl[ 9] * proj[ 6] + modl[10] * proj[10] + modl[11] * proj[14];
    // clip[11] = modl[ 8] * proj[ 3] + modl[ 9] * proj[ 7] + modl[10] * proj[11] + modl[11] * proj[15];

    // clip[12] = modl[12] * proj[ 0] + modl[13] * proj[ 4] + modl[14] * proj[ 8] + modl[15] * proj[12];
    // clip[13] = modl[12] * proj[ 1] + modl[13] * proj[ 5] + modl[14] * proj[ 9] + modl[15] * proj[13];
    // clip[14] = modl[12] * proj[ 2] + modl[13] * proj[ 6] + modl[14] * proj[10] + modl[15] * proj[14];
    // clip[15] = modl[12] * proj[ 3] + modl[13] * proj[ 7] + modl[14] * proj[11] + modl[15] * proj[15];



    _Frustum[eRight][eA] = clip[ 3] - clip[ 0];
    _Frustum[eRight][eB] = clip[ 7] - clip[ 4];
    _Frustum[eRight][eC] = clip[11] - clip[ 8];
    _Frustum[eRight][eD] = clip[15] - clip[12];
    normalizePlane(eRight);

    _Frustum[eLeft][eA] = clip[ 3] + clip[ 0];
    _Frustum[eLeft][eB] = clip[ 7] + clip[ 4];
    _Frustum[eLeft][eC] = clip[11] + clip[ 8];
    _Frustum[eLeft][eD] = clip[15] + clip[12];
    normalizePlane(eLeft);


    _Frustum[eBottom][eA] = clip[ 3] + clip[ 1];
    _Frustum[eBottom][eB] = clip[ 7] + clip[ 5];
    _Frustum[eBottom][eC] = clip[11] + clip[ 9];
    _Frustum[eBottom][eD] = clip[15] + clip[13];
    normalizePlane(eBottom);

    _Frustum[eTop][eA] = clip[ 3] - clip[ 1];
    _Frustum[eTop][eB] = clip[ 7] - clip[ 5];
    _Frustum[eTop][eC] = clip[11] - clip[ 9];
    _Frustum[eTop][eD] = clip[15] - clip[13];
    normalizePlane(eTop);


    _Frustum[eBack][eA] = clip[ 3] - clip[ 2];
    _Frustum[eBack][eB] = clip[ 7] - clip[ 6];
    _Frustum[eBack][eC] = clip[11] - clip[10];
    _Frustum[eBack][eD] = clip[15] - clip[14];
    normalizePlane(eBack);

    _Frustum[eFront][eA] = clip[ 3] + clip[ 2];
    _Frustum[eFront][eB] = clip[ 7] + clip[ 6];
    _Frustum[eFront][eC] = clip[11] + clip[10];
    _Frustum[eFront][eD] = clip[15] + clip[14];
    normalizePlane(eFront);

}

bool	GL_FrustumCulling::pointInFrustum( float x, float y, float z ) const
{
    for (int i = 0; i < 6; ++i)
        if ( _Frustum[i][eA] * x +
             _Frustum[i][eB] * y +
             _Frustum[i][eC] * z +
             _Frustum[i][eD] <= 0 )
            return false;

    return true;
}

bool	GL_FrustumCulling::sphereInFrustum( float x, float y, float z, float radius ) const
{
    for (int i = 0; i < 6; ++i)
        if ( _Frustum[i][eA] * x +
             _Frustum[i][eB] * y +
             _Frustum[i][eC] * z +
             _Frustum[i][eD] <= -radius )
            return false;

    return true;
}

bool	GL_FrustumCulling::cubeInFrustum( float x, float y, float z, float size ) const
{
    for (int i = 0; i < 6; ++i)
    {
        if (_Frustum[i][eA] * (x - size) +
                _Frustum[i][eB] * (y - size) +
                _Frustum[i][eC] * (z - size) +
                _Frustum[i][eD] > 0)
            continue;

        if (_Frustum[i][eA] * (x + size) +
                _Frustum[i][eB] * (y - size) +
                _Frustum[i][eC] * (z - size) +
                _Frustum[i][eD] > 0)
            continue;

        if (_Frustum[i][eA] * (x - size) +
                _Frustum[i][eB] * (y + size) +
                _Frustum[i][eC] * (z - size) +
                _Frustum[i][eD] > 0)
            continue;

        if (_Frustum[i][eA] * (x + size) +
                _Frustum[i][eB] * (y + size) +
                _Frustum[i][eC] * (z - size) +
                _Frustum[i][eD] > 0)
            continue;

        ///

        if (_Frustum[i][eA] * (x - size) +
                _Frustum[i][eB] * (y - size) +
                _Frustum[i][eC] * (z + size) +
                _Frustum[i][eD] > 0)
            continue;

        if (_Frustum[i][eA] * (x + size) +
                _Frustum[i][eB] * (y - size) +
                _Frustum[i][eC] * (z + size) +
                _Frustum[i][eD] > 0)
            continue;

        if (_Frustum[i][eA] * (x - size) +
                _Frustum[i][eB] * (y + size) +
                _Frustum[i][eC] * (z + size) +
                _Frustum[i][eD] > 0)
            continue;

        if (_Frustum[i][eA] * (x + size) +
                _Frustum[i][eB] * (y + size) +
                _Frustum[i][eC] * (z + size) +
                _Frustum[i][eD] > 0)
            continue;

        return false;
    }

    return true;
}


bool	GL_FrustumCulling::cubeInFrustum(const Vec3f& v, const Vec3f& s2) const
{
    Vec3f	s(s2);
    s.x *= 0.5;
    s.y *= 0.5;
    s.z *= 0.5;

    for (int i = 0; i < 6; ++i)
    {
        if (_Frustum[i][eA] * (v.x - s.x) +
                _Frustum[i][eB] * (v.y - s.y) +
                _Frustum[i][eC] * (v.z - s.z) +
                _Frustum[i][eD] > 0)
            continue;

        if (_Frustum[i][eA] * (v.x + s.x) +
                _Frustum[i][eB] * (v.y - s.y) +
                _Frustum[i][eC] * (v.z - s.z) +
                _Frustum[i][eD] > 0)
            continue;

        if (_Frustum[i][eA] * (v.x - s.x) +
                _Frustum[i][eB] * (v.y + s.y) +
                _Frustum[i][eC] * (v.z - s.z) +
                _Frustum[i][eD] > 0)
            continue;

        if (_Frustum[i][eA] * (v.x + s.x) +
                _Frustum[i][eB] * (v.y + s.y) +
                _Frustum[i][eC] * (v.z - s.z) +
                _Frustum[i][eD] > 0)
            continue;

        if (_Frustum[i][eA] * (v.x - s.x) +
                _Frustum[i][eB] * (v.y - s.y) +
                _Frustum[i][eC] * (v.z + s.z) +
                _Frustum[i][eD] > 0)
            continue;

        if (_Frustum[i][eA] * (v.x + s.x) +
                _Frustum[i][eB] * (v.y - s.y) +
                _Frustum[i][eC] * (v.z + s.z) +
                _Frustum[i][eD] > 0)
            continue;

        if (_Frustum[i][eA] * (v.x - s.x) +
                _Frustum[i][eB] * (v.y + s.y) +
                _Frustum[i][eC] * (v.z + s.z) +
                _Frustum[i][eD] > 0)
            continue;

        if (_Frustum[i][eA] * (v.x + s.x) +
                _Frustum[i][eB] * (v.y + s.y) +
                _Frustum[i][eC] * (v.z + s.z) +
                _Frustum[i][eD] > 0)
            continue;

        return false;
    }

    return true;
}


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////



//void	GL_FrustumCulling::CalcOrtho( Vec3f eye, Vec3f target,
//                                      float left, float right,
//                                      float bottom, float top,
//                                      float nearval, float farval )
//{

//    /**

//       float   proj[16];
//       float   modl[16];


//       glMatrixMode(GL_PROJECTION);

//       glPushMatrix();
//       {
//       glLoadIdentity();

//       glOrtho( left, right,
//       bottom, top,
//       nearval, farval );

//       glGetFloatv( GL_PROJECTION_MATRIX, proj );
//       }
//       glPopMatrix();


//       glMatrixMode(GL_MODELVIEW);

//       glPushMatrix();
//       {
//       glLoadIdentity();

//       gluLookAt( eye.x, eye.y, eye.z,
//       target.x, target.y, target.z,
//       0,0,1 );

//       glGetFloatv( GL_MODELVIEW_MATRIX, modl );
//       }
//       glPopMatrix();


//       CalculateFrustum(proj, modl);

//    //*/
//}


//void	GL_FrustumCulling::CalcPerspective( Vec3f eye, Vec3f target,
//                                            float angle, float aspect_ratio,
//                                            float nearval, float farval )
//{

//    /**

//       float   proj[16];
//       float   modl[16];


//       glMatrixMode(GL_PROJECTION);

//       glPushMatrix();
//       {
//       glLoadIdentity();

//       gluPerspective(angle, aspect_ratio, nearval, farval);

//       glGetFloatv( GL_PROJECTION_MATRIX, proj );
//       }
//       glPopMatrix();


//       glMatrixMode(GL_MODELVIEW);

//       glPushMatrix();
//       {
//       glLoadIdentity();

//       gluLookAt( eye.x, eye.y, eye.z,
//       target.x, target.y, target.z,
//       0,0,1 );

//       glGetFloatv( GL_MODELVIEW_MATRIX, modl );
//       }
//       glPopMatrix();


//       CalculateFrustum(proj, modl);

//    //*/
//}

//////////////////////////////////////////////////////////////////////////////

//void	GL_FrustumCulling::DrawOrtho( Vec3f eye, Vec3f target,
//                                      float left, float right,
//                                      float bottom, float top,
//                                      float nearval, float farval )
//{
//    float	theta = 0;
//    float	phi = 0;

//    {
//        Vec3f	diff;
//        diff.x = target.x - eye.x;
//        diff.y = target.y - eye.y;
//        diff.z = target.z - eye.z;
//        theta = atan2f(diff.y, diff.x) * 180.0f / 3.14f;

//        Vec2f	vec;
//        vec.x = fast_sqrtf( diff.x * diff.x + diff.y * diff.y );
//        vec.y = -diff.z;
//        phi = atan2f(vec.y, vec.x) * 180.0f / 3.14f;
//    }


//    Vec3f	vertices[8];
//    {
//        vertices[0] = Vec3f(nearval, left,  top);
//        vertices[1] = Vec3f(nearval, right, top);
//        vertices[2] = Vec3f(nearval, left,  bottom);
//        vertices[3] = Vec3f(nearval, right, bottom);

//        vertices[4] = Vec3f(farval, left,  top);
//        vertices[5] = Vec3f(farval, right, top);
//        vertices[6] = Vec3f(farval, left,  bottom);
//        vertices[7] = Vec3f(farval, right, bottom);
//    }


//    int	indices[] = {
//        0,1, 1,3, 3,2, 2,0,
//        0,4, 1,5, 2,6, 3,7,
//        4,5, 5,7, 7,6, 6,4
//    };

//    int	indices2[] = {
//        0,1,3,2, 0,1,5,4, 0,2,6,4,
//        4,5,7,6, 2,3,7,6, 1,3,7,5
//    };

//    glPushMatrix();
//    {
//        glTranslatef(eye.x, eye.y, eye.z);
//        glRotatef(theta, 0,0,1);
//        glRotatef(phi, 0,1,0);

//        glDisable(GL_BLEND);
//        glBegin(GL_LINES);
//        {
//            for (int i = 0; i < 24; ++i)
//                glVertex3fv( &(vertices[ indices[i] ].x) );
//        }
//        glEnd();

//        glEnable(GL_BLEND);
//        glBegin(GL_QUADS);
//        {
//            for (int i = 0; i < 24; ++i)
//                glVertex3fv( &(vertices[ indices2[i] ].x) );
//        }
//        glEnd();
//    }
//    glPopMatrix();

//}


//void	GL_FrustumCulling::DrawPerspective( Vec3f eye, Vec3f target,
//                                            float angle, float aspect_ratio,
//                                            float nearval, float farval )
//{
//    float	theta = 0;
//    float	phi = 0;

//    {
//        Vec3f	diff;
//        diff.x = target.x - eye.x;
//        diff.y = target.y - eye.y;
//        diff.z = target.z - eye.z;
//        theta = atan2f(diff.y, diff.x) * 180.0f / 3.14f;

//        Vec2f	vec;
//        vec.x = fast_sqrtf( diff.x * diff.x + diff.y * diff.y );
//        vec.y = -diff.z;
//        phi = atan2f(vec.y, vec.x) * 180.0f / 3.14f;
//    }


//    Vec3f	vertices[8];
//    {
//        float	left, right, bottom, top;

//#define	D_PERSPECTIVE(fovY, aspect, zNear, zFar)	\
//        {							\
//    const GLdouble pi = 3.1415926f;			\
//    GLdouble fW, fH;				\
//    \
//    fH = tan( fovY / 360.0 * pi ) * zNear;		\
//    fW = fH * aspect;				\
//    \
//    left = -fW;					\
//    right = +fW;					\
//    \
//    top = +fH;					\
//    bottom = -fH;					\
//    }

//        D_PERSPECTIVE(angle, aspect_ratio, nearval, farval);

//#undef	D_PERSPECTIVE

//        vertices[0] = Vec3f(nearval, left,  top);
//        vertices[1] = Vec3f(nearval, right, top);
//        vertices[2] = Vec3f(nearval, left,  bottom);
//        vertices[3] = Vec3f(nearval, right, bottom);

//        float	half_y = farval * sinf(angle * 3.14f / 180.0f);
//        float	half_z = half_y / aspect_ratio;

//        vertices[4] = Vec3f( farval, -half_y, +half_z );
//        vertices[5] = Vec3f( farval, +half_y, +half_z );
//        vertices[6] = Vec3f( farval, -half_y, -half_z );
//        vertices[7] = Vec3f( farval, +half_y, -half_z );
//    }


//    unsigned int	indices[] = {
//        0,1, 1,3, 3,2, 2,0,
//        0,4, 1,5, 2,6, 3,7,
//        4,5, 5,7, 7,6, 6,4
//    };

//    unsigned int	indices2[] = {
//        0,1,3,2, 0,1,5,4, 0,2,6,4,
//        4,5,7,6, 2,3,7,6, 1,3,7,5
//    };




//    glPushMatrix();
//    {
//        glTranslatef(eye.x, eye.y, eye.z);
//        glRotatef(theta, 0,0,1);
//        glRotatef(phi, 0,1,0);



//        glEnableClientState(GL_VERTEX_ARRAY);
//        glVertexPointer( 3, GL_FLOAT, 0, &(vertices[0].x) );

//        glDisable(GL_BLEND);
//        glColor4f(1,1,1,1);
//        glDrawElements( GL_LINES, 24, GL_UNSIGNED_INT, indices );

//        glEnable(GL_BLEND);
//        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//        glColor4f(1,1,1,0.2);
//        glDrawElements( GL_QUADS, 24, GL_UNSIGNED_INT, indices2 );

//        glDisableClientState(GL_VERTEX_ARRAY);




//        /**

//        glBegin(GL_LINES);
//        {
//            for (int i = 0; i < 24; ++i)
//                glVertex3fv( &(vertices[ indices[i] ].x) );
//        }
//        glEnd();

//        glEnable(GL_BLEND);
//        glBegin(GL_QUADS);
//        {
//            for (int i = 0; i < 24; ++i)
//                glVertex3fv( &(vertices[ indices2[i] ].x) );
//        }
//        glEnd();

//        //*/

//    }
//    glPopMatrix();

//}

}; // namespace	myGL

