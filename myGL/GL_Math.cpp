

#include "GL_Math.hpp"


namespace	myGL
{

  template <typename T>
  T	fast_invsqrt(T x)
  {
    static_cast<void>(x);
    return (0);
  }

  template <>
  double	fast_invsqrt(double x)
  {
    union {
      double	u_d;
      long int	u_i;
    }		tmp;

    tmp.u_d = x;
    tmp.u_i = 0x5fe6eb50c7b537a9 - (tmp.u_i >> 1);

    double	y = tmp.u_d;

    return (y * (1.5f - 0.5f * x * y * y));
  }

  template <>
  float		fast_invsqrt(float x)
  {
    union {
      float	u_f;
      int		u_i;
    }		tmp;

    tmp.u_f = x;
    tmp.u_i = 0x5f3759df - (tmp.u_i >> 1);

    float		y = tmp.u_f;

    return (y * (1.5f - 0.5f * x * y * y));
  }

}; // namespace	myGL

