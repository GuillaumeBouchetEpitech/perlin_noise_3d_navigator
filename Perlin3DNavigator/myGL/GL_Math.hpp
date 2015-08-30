

#ifndef	GL_MATH_HPP
#define	GL_MATH_HPP


#include <cstdlib>
#include <cmath>


namespace	myGL
{

  // double	fast_invsqrtd(double x);

  // inline double	fast_sqrtd(double x)
  // {
  //   return (1.0 / fast_invsqrtd(x));
  // }

  // float	fast_invsqrtf(float x);

  // inline float	fast_sqrtf(float x)
  // {
  //   return (1.0f / fast_invsqrtf(x));
  // }


  template <typename T>
  T	fast_invsqrt(T x);

  template <>
  float	fast_invsqrt(float x);

  template <>
  double	fast_invsqrt(double x);

  ////

  template <typename T>
  inline T	fast_sqrt(T x);

  template <>
  inline float	fast_sqrt(float x)
  {
    return (1.0f / fast_invsqrt(x));
  }

  template <>
  inline double	fast_sqrt(double x)
  {
    return (1.0 / fast_invsqrt(x));
  }


}; // namespace	myGL


#endif	// GL_MATH_HPP

