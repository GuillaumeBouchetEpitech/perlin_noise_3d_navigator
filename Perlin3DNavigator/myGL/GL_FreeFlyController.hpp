

#ifndef	CAMERA_FREEFLY_HH
#define	CAMERA_FREEFLY_HH


#define _USE_MATH_DEFINES
#include <cmath>


#include "GL_Matrix.hpp"

#include "GL_FrustumCulling.hpp"

#include "GL_Vec2.hpp"
#include "GL_Vec3.hpp"



namespace	myGL
{

class	GL_FreeFlyController
{
private :

    Vec3f		_Position;
    Vec3f		_Forward;
    Vec3f		_Up;
    Vec3f		_Left;
    Vec3f		_Target;

    float			_speed;
    float			_sensivity;
    float			_theta;
    float			_phi;

//    GL_Matrix		_Mat4x4_proj;
//    GL_Matrix		_Mat4x4_view;

    // GL_FrustumCulling	_Frustum;

public :

    int     _sens_l, _sens_f;
    float	_mouse_dec_x, _mouse_dec_y;

public : // ctor / dtor

    GL_FreeFlyController();

public : // init

    void	initialize();

//    void	resize(int width, int height);

public : // step

    void	advance(GL_Matrix& viewMatrix, const float ratio = 1.0f);

public : // getter

    inline const Vec3f& getPosition() const { return (_Position); }
    inline const Vec3f& getForward() const  { return (_Forward); }
    inline const Vec3f& getTarget() const  { return (_Target); }

    inline float    getPhi() const      { return (_phi); }
    inline float    getTheta() const	{ return (_theta); }

    //const GL_FrustumCulling&	getFrustum() const	{return (_Frustum);}


//    const GL_Matrix&	get_ViewMatrix() const          {return (_Mat4x4_view);}
//    const GL_Matrix&	get_ProjectionMatrix() const    {return (_Mat4x4_proj);}


private : // utils

    void	vectorsFromAngles();


public : // utils

    inline float	getSpeed() const        { return (_speed); }
    inline void     setSpeed(float speed)   { _speed = speed; }

    //  public :

    //    bool	get3DPoint(const Vec2f& Mouse, Vec3f& Position);
    //    bool	get2DPoint(const Vec3f& Target, Vec2f& Position);

    //    //void	Do_BillBoard(const Vec3f& Object_Pos);

    //  public :

    //    void    Render(int width, int height);

};

}; // namespace	myGL


#endif

