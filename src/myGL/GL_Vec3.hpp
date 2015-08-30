

#ifndef	GL_VEC3_HPP
#define	GL_VEC3_HPP


#include "GL_Math.hpp"


namespace myGL
{

template <typename T>
struct Vec3
{
public :

    Vec3();

    Vec3(T X, T Y, T Z);

    template <typename U>
    explicit Vec3(const Vec3<U>& vector);

    T x, y, z;
};

template <typename T>
Vec3<T> operator -(const Vec3<T>& left);

template <typename T>
Vec3<T>& operator +=(Vec3<T>& left, const Vec3<T>& right);

template <typename T>
Vec3<T>& operator -=(Vec3<T>& left, const Vec3<T>& right);

template <typename T>
Vec3<T> operator +(const Vec3<T>& left, const Vec3<T>& right);

template <typename T>
Vec3<T> operator -(const Vec3<T>& left, const Vec3<T>& right);

template <typename T>
Vec3<T> operator *(const Vec3<T>& left, T right);

template <typename T>
Vec3<T> operator *(T left, const Vec3<T>& right);

template <typename T>
Vec3<T>& operator *=(Vec3<T>& left, T right);

template <typename T>
Vec3<T> operator /(const Vec3<T>& left, T right);

template <typename T>
Vec3<T>& operator /=(Vec3<T>& left, T right);

///////////////////////////////

template <typename T>
bool operator ==(const Vec3<T>& left, const Vec3<T>& right);

template <typename T>
bool operator !=(const Vec3<T>& left, const Vec3<T>& right);

template <typename T>
bool operator <(const Vec3<T>& left, const Vec3<T>& right);

///////////////////////////////

template <typename T>
static T	length2(T x, T y, T z);

template <typename T>
static T	length2(const Vec3<T>& v);

template <typename T>
static T	length2(const Vec3<T>& v1, const Vec3<T>& v2);

///////////////////////////////

template <typename T>
static T	length(T x, T y);

template <typename T>
static T	length(const Vec3<T>& v);

template <typename T>
static T	length(const Vec3<T>& v1, const Vec3<T>& v2);

///////////////////////////////

template <typename T>
static void	normalize(Vec3<T>& v);

#include "GL_Vec3.inl"

typedef Vec3<int>		Vec3i;
typedef Vec3<unsigned int>	Vec3u;
typedef Vec3<float>		Vec3f;

} // namespace	myGL



#endif	// GL_VEC3_HPP

