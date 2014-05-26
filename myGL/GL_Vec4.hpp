

#ifndef	GL_VEC4_HPP
#define	GL_VEC4_HPP


#include "GL_Math.hpp"


namespace myGL
{

template <typename T>
struct Vec4
{
public :

    Vec4();

    Vec4(T X, T Y, T Z, T W);

    template <typename U>
    explicit Vec4(const Vec4<U>& vector);

    T x, y, z, w;
};

template <typename T>
Vec4<T> operator -(const Vec4<T>& left);

template <typename T>
Vec4<T>& operator +=(Vec4<T>& left, const Vec4<T>& right);

template <typename T>
Vec4<T>& operator -=(Vec4<T>& left, const Vec4<T>& right);

template <typename T>
Vec4<T> operator +(const Vec4<T>& left, const Vec4<T>& right);

template <typename T>
Vec4<T> operator -(const Vec4<T>& left, const Vec4<T>& right);

template <typename T>
Vec4<T> operator *(const Vec4<T>& left, T right);

template <typename T>
Vec4<T> operator *(T left, const Vec4<T>& right);

template <typename T>
Vec4<T>& operator *=(Vec4<T>& left, T right);

template <typename T>
Vec4<T> operator /(const Vec4<T>& left, T right);

template <typename T>
Vec4<T>& operator /=(Vec4<T>& left, T right);

///////////////////////////////

template <typename T>
bool operator ==(const Vec4<T>& left, const Vec4<T>& right);

template <typename T>
bool operator !=(const Vec4<T>& left, const Vec4<T>& right);

template <typename T>
bool operator <(const Vec4<T>& left, const Vec4<T>& right);

///////////////////////////////

template <typename T>
static T	length2(T x, T y, T z, T w);

template <typename T>
static T	length2(const Vec4<T>& v);

template <typename T>
static T	length2(const Vec4<T>& v1, const Vec4<T>& v2);

///////////////////////////////

template <typename T>
static T	length(T x, T y);

template <typename T>
static T	length(const Vec4<T>& v);

template <typename T>
static T	length(const Vec4<T>& v1, const Vec4<T>& v2);

///////////////////////////////

template <typename T>
static void	normalize(Vec4<T>& v);

#include "GL_Vec4.inl"

typedef Vec4<int>		Vec4i;
typedef Vec4<unsigned int>	Vec4u;
typedef Vec4<float>		Vec4f;

} // namespace	myGL



#endif	// GL_VEC4_HPP

