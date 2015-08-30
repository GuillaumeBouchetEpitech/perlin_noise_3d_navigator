

#ifndef	GL_VEC2_HPP
#define	GL_VEC2_HPP


#include "GL_Math.hpp"


namespace	myGL
{

  template <typename T>
  struct	Vec2
  {
  public :

    Vec2();
    Vec2(T X, T Y);

    template <typename U>
    explicit Vec2(const Vec2<U>& vector);

    T x, y;
  };

  template <typename T>
  Vec2<T> operator -(const Vec2<T>& right);

  template <typename T>
  Vec2<T>& operator +=(Vec2<T>& left, const Vec2<T>& right);

  template <typename T>
  Vec2<T>& operator -=(Vec2<T>& left, const Vec2<T>& right);

  template <typename T>
  Vec2<T> operator +(const Vec2<T>& left, const Vec2<T>& right);

  template <typename T>
  Vec2<T> operator -(const Vec2<T>& left, const Vec2<T>& right);

  template <typename T>
  Vec2<T> operator *(const Vec2<T>& left, T right);

  template <typename T>
  Vec2<T> operator *(T left, const Vec2<T>& right);

  template <typename T>
  Vec2<T>& operator *=(Vec2<T>& left, T right);

  template <typename T>
  Vec2<T> operator /(const Vec2<T>& left, T right);

  template <typename T>
  Vec2<T>& operator /=(Vec2<T>& left, T right);

  ///////////////////////////////

  template <typename T>
  bool operator ==(const Vec2<T>& left, const Vec2<T>& right);

  template <typename T>
  bool operator !=(const Vec2<T>& left, const Vec2<T>& right);

  ///////////////////////////////

  template <typename T>
  static T	length2(T x, T y);

  template <typename T>
  static T	length2(const Vec2<T>& v);

  template <typename T>
  static T	length2(const Vec2<T>& v1, const Vec2<T>& v2);

  ///////////////////////////////

  template <typename T>
  static T	length(T x, T y);

  template <typename T>
  static T	length(const Vec2<T>& v);

  template <typename T>
  static T	length(const Vec2<T>& v1, const Vec2<T>& v2);

  ///////////////////////////////

  template <typename T>
  static void	normalize(Vec2<T>& v);

#include "GL_Vec2.inl"

  typedef Vec2<int>		Vec2i;
  typedef Vec2<unsigned int>	Vec2u;
  typedef Vec2<float>		Vec2f;

}; // namespace	myGL


#endif	// GL_VEC2_HPP

