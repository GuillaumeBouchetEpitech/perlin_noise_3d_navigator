

#include "GL_FreeFlyController.hpp"

#include <iostream>


namespace	myGL
{

// GL_FreeFlyController::GL_FreeFlyController(sf::RenderWindow& RWindow)
//   : _RWindow(RWindow)
GL_FreeFlyController::GL_FreeFlyController()
{
    _Position = Vec3f(0, 0, 0);
    _speed = 30;
    _sensivity = 0.1;
    _phi = 0;
    _theta = 0;

    //vectorsFromAngles();
}

void	GL_FreeFlyController::vectorsFromAngles()
{
    Vec3f	Up(0,0,1);

    if (_phi >= 89)
        _phi = 89;
    else if (_phi <= -89)
        _phi = -89;

    if (_theta > 360)
        _theta -= 360;
    else if (_theta < 0)
        _theta += 360;

    float	upRadius = cosf((_phi - 90.0f) * M_PI / 180);
    Up.z = sinf( (_phi - 90.0f) * M_PI / 180.0f);
    Up.x = upRadius * cosf(_theta * M_PI / 180.0f);
    Up.y = upRadius * sinf(_theta * M_PI / 180.0f);

    float	forwardRadius = cosf(_phi * M_PI / 180.0f);
    _Forward.z = sin(_phi * M_PI / 180.0f);
    _Forward.x = forwardRadius * cosf(_theta * M_PI / 180.0f);
    _Forward.y = forwardRadius * sinf(_theta * M_PI / 180.0f);

    _Left.x = Up.y * _Forward.z - Up.z * _Forward.y;
    _Left.y = Up.z * _Forward.x - Up.x * _Forward.z;
    _Left.z = Up.x * _Forward.y - Up.y * _Forward.x;

    _Target.x = _Position.x + _Forward.x;
    _Target.y = _Position.y + _Forward.y;
    _Target.z = _Position.z + _Forward.z;

    //    _Mat4x4_view.Make_LookAt( _Position,
    //                              _Target,
    //                              Vec3f(0,0,1) );

    //_Frustum.calculateFrustum( _Mat4x4_proj, _Mat4x4_view );

}

//void	GL_FreeFlyController::resize(int width, int height)
//{
//    double  aspectRatio = static_cast<double>(width) / height;

//    _Mat4x4_proj.Make_Perspective( 70.0, aspectRatio, 0.1,500.0 );

//    vectorsFromAngles();
//}

void	GL_FreeFlyController::advance(GL_Matrix& viewMatrix, const float ratio /*= 1.0f*/)
{

    _theta	-= (_mouse_dec_x) * _sensivity;
    _phi	-= (_mouse_dec_y) * _sensivity;

    vectorsFromAngles();

    viewMatrix.Make_LookAt( _Position,
                            _Target,
                            Vec3f(0,0,1) );

    if      (_sens_l < 0) _Position -= _Left * _speed * ratio;
    else if (_sens_l > 0) _Position += _Left * _speed * ratio;

    if      (_sens_f > 0) _Position +=  _Forward * _speed * ratio;
    else if (_sens_f < 0) _Position -=  _Forward * _speed * ratio;

    _Target.x = _Position.x + _Forward.x;
    _Target.y = _Position.y + _Forward.y;
    _Target.z = _Position.z + _Forward.z;

}


////////////////////////////////////////////////////
////////////////////////////////////////////////////


//bool	GL_FreeFlyController::get3DPoint(int* pViewport, const Vec2f& Target, Vec3f& Position)
//{
//    int viewport[4];

//    glGetIntegerv( GL_VIEWPORT, viewport );

//    float	winX, winY, winZ;
//    double	posX, posY, posZ;

//    winX = Target.x;
//    //winY = (float)viewport[3] - Target.y;
//    winY = (float)pViewport[3] - Target.y;

//    glReadPixels( int(winX), int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

//    {
//        float in[4];
//        float out[4];
//        out[3] = 0.0f;

//        GL_Matrix	my_finalMatrix = _Mat4x4_proj * _Mat4x4_view;
//        GL_Matrix	my_inv_finalMatrix = _Mat4x4_proj * _Mat4x4_view;

//        if (!my_finalMatrix.getInverse( my_inv_finalMatrix ))
//        {
//            std::cerr << "my___gluInvertMatrixd" << std::endl;
//            return (false);
//        }

//        in[0] = winX;
//        in[1] = winY;
//        in[2] = winZ;
//        in[3] = 1.0;

//        // std::cerr << "winZ : " << winZ << std::endl;

//        /* Map x and y from window coordinates */
//        in[0] = (in[0] - viewport[0]) / viewport[2];
//        in[1] = (in[1] - viewport[1]) / viewport[3];

//        /* Map to range -1 to 1 */
//        in[0] = in[0] * 2 - 1;
//        in[1] = in[1] * 2 - 1;
//        in[2] = in[2] * 2 - 1;

//        my_inv_finalMatrix.PreMult( in, out );

//        if (out[3] == 0.0f)
//        {
//            std::cerr << "my___gluMultMatrixVecd" << std::endl;
//            return (false);
//        }

//        out[0] /= out[3];
//        out[1] /= out[3];
//        out[2] /= out[3];

//        posX = out[0];
//        posY = out[1];
//        posZ = out[2];
//    }

//    Position.x = posX;
//    Position.y = posY;
//    Position.z = posZ;

//    return (true);
//}

//bool	GL_FreeFlyController::get2DPoint(const Vec3f& Target, Vec2f& Position)
//{
//    // unsigned int	Width = _RWindow.getSize().x;
//    // unsigned int	Height = _RWindow.getSize().y;

//    int	viewport[4];
//    glGetIntegerv( GL_VIEWPORT, viewport );

//    // viewport[0] = 0;
//    // viewport[1] = 0;
//    // viewport[2] = Width;
//    // viewport[3] = Height;

//    float	in[4];
//    float	out[4];

//    in[0] = Target.x;
//    in[1] = Target.y;
//    in[2] = Target.z;
//    in[3] = 1;

//    _Mat4x4_view.PreMult( in, out );
//    _Mat4x4_proj.PreMult( out, in );

//    in[0] /= in[3];
//    in[1] /= in[3];
//    in[2] /= in[3];

//    in[0] = in[0] * 0.5f + 0.5f;
//    in[1] = in[1] * 0.5f + 0.5f;
//    in[2] = in[2] * 0.5f + 0.5f;

//    in[0] = in[0] * viewport[2] + viewport[0];
//    in[1] = in[1] * viewport[3] + viewport[1];

//    Position.x = in[0];
//    Position.y = (float)viewport[3] - in[1];

//    return (true);
//}

///**
//void	GL_FreeFlyController::Do_BillBoard(const Vec3f& Object_Pos)
//{

//    //// GET THETA

//    float	theta = atan2f( Object_Pos.y - _Position.y,
//                            Object_Pos.x - _Position.x );

//    //// GET PHI

//#define	D_SQ(v) ((v) * (v))
//#define	D_LENGTH(v1, v2) sqrtf( D_SQ((v1).x - (v2).x) + D_SQ((v1).y - (v2).y) )

//    Vec2f	Profile_Pos;

//    Profile_Pos.x = D_LENGTH( Object_Pos, _Position );
//    Profile_Pos.y = _Position.z - Object_Pos.z;

//#undef	D_LENGTH
//#undef	D_SQ

//    float	phi = atan2f( Profile_Pos.y, Profile_Pos.x );

//    //// APPLY

//    glTranslatef( Object_Pos.x, Object_Pos.y, Object_Pos.z );

//#define	D_RADIAN_TO_DEGREE(rad) ((rad) * 180.0f / 3.14f)

//    glRotatef( D_RADIAN_TO_DEGREE(theta), 0,0,1 );
//    glRotatef( D_RADIAN_TO_DEGREE(phi), 0,1,0 );

//#undef	D_RADIAN_TO_DEGREE

//}
///**

//void    GL_FreeFlyController::Render(int width, int height)
//{

//    double	aspectRatio = static_cast<double>(width) / height;


//    _Frustum.DrawPerspective( _Position, _Target,
//                               70, aspectRatio,
//                               0.1, 500.0 );

//}
////*/

}; // namespace	myGL

