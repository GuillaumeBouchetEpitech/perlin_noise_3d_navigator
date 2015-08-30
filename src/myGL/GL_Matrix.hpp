

#ifndef GL_MATRIX_HPP
#define GL_MATRIX_HPP



#include "GL_Vec3.hpp"

#include <cstring>


namespace	myGL
{

  class	GL_Matrix
  {
  protected :

    union
    {
      float	_mat[4][4];
      float	_tab[16];
    };

  public :

    inline GL_Matrix()
    {
      Make_Identity();
    }

  private :

    int	Compare(const GL_Matrix& m) const;

  public :

    inline bool	operator == (const GL_Matrix& m) const
    {
      return (Compare(m) == 0);
    }

    inline bool	operator != (const GL_Matrix& m) const
    {
      return (Compare(m) != 0);
    }

  public :

    inline float& operator()(int row, int col)
    {
      return (_mat[row][col]);
    }

    inline float operator()(int row, int col) const
    {
      return (_mat[row][col]);
    }

  public :

    inline float& operator[](unsigned int idx)
    {
      return (_tab[idx]);
    }

    inline float operator[](unsigned int idx) const
    {
      return (_tab[idx]);
    }

  public :

    inline void	get(float *ptr) const
    {
      memcpy(ptr, _tab, 16 * sizeof(float));
    }

    inline const float*	Ptr() const
    {
      return (_tab);
    }

  public :

    GL_Matrix&	operator = (const GL_Matrix& rhs);

  public :

    inline void Set(float const * const ptr)
    {
      memcpy(_tab, ptr, 16 * sizeof(float));
    }

    inline void Set(const GL_Matrix& mat)
    {
      memcpy(_tab, mat._tab, 16 * sizeof(float));
    }

  public :

    bool	IsIdentity() const;
    void	Make_Identity();

  public :

    void	Make_Scale(float x, float y, float z);

    inline void	Make_Scale(const Vec3f& v3)
    {
      Make_Scale(v3.x, v3.y, v3.z);
    }

  public :

    void	Make_Translate(float x, float y, float z);

    inline void	Make_Translate(const Vec3f& v3)
    {
      Make_Translate(v3.x, v3.y, v3.z);
    }

  public :

    void	Make_Rotate(float angle, float x, float y, float z);

    inline void	Make_Rotate(float angle, const Vec3f& axis)
    {
      Make_Rotate(angle, axis.x, axis.y, axis.z);
    }

  public :

    void	Make_Ortho( float left,   float right,
			    float bottom, float top,
			    float zNear,  float zFar );

  public :

    void	Make_Frustum( float left,   float right,
			      float bottom, float top,
			      float zNear,  float zFar );

  public :

    void	Make_Perspective( float fovy,  float aspectRatio,
				  float zNear, float zFar );

  public :

    void	Make_LookAt( const Vec3f& eye,
			     const Vec3f& center,
			     const Vec3f& up );

  public :

    Vec3f PreMult(const Vec3f& v) const;
    Vec3f PostMult(const Vec3f& v) const;

    inline Vec3f	operator * (const Vec3f& v) const
    {
      return (PostMult(v));
    }

    inline GL_Matrix	operator * (const GL_Matrix& m) const
    {
      GL_Matrix	ret_val;
      ret_val.Set(*this);
      ret_val.PreMult(m);
      return (ret_val);
    }

  public :

    // Vec3f PreMult(const float* v4) const;
    // Vec3f PostMult(const float* v4) const;
    void	PreMult(const float* v4_in, float* v4_out) const;
    void	PostMult(const float* v4_in, float* v4_out) const;

    // inline Vec3f operator * (const Vec3f& v) const
    // {
    //   // return (PostMult(v));
    //   return (PreMult(v));
    // }

  public :

    void	Mult(const GL_Matrix& lhs, const GL_Matrix& rhs);

    void	PreMult(const GL_Matrix& other);
    void	PostMult(const GL_Matrix& other);

    ///

    bool	getInverse( GL_Matrix& out );

    ///

    void	PreMultTranslate(const Vec3f& v);
    inline void	PreMultTranslate(const Vec3i& v)
    {
        PreMultTranslate( Vec3f(v.x, v.y, v.z) );
    }

    void	PostMultTranslate(const Vec3f& v);

    void	PreMultScale(const Vec3f& v3);
    void	PostMultScale(const Vec3f& v3);

    void	PreMultRotate(float angle, float x, float y, float z);
    void	PostMultRotate(float angle, float x, float y, float z);

  };

}; // namespace	myGL


#endif	// GL_MATRIX_HPP

