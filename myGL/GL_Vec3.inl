

template <typename T>
inline Vec3<T>::Vec3()
  : x(0), y(0), z(0)
{

}

template <typename T>
inline Vec3<T>::Vec3(T X, T Y, T Z)
  : x(X), y(Y), z(Z)
{

}

template <typename T>
template <typename U>
inline Vec3<T>::Vec3(const Vec3<U>& vector)
  : x(static_cast<T>(vector.x)),
    y(static_cast<T>(vector.y)),
    z(static_cast<T>(vector.z))
{
}

////////////////////////////////////////////////////////////

template <typename T>
inline Vec3<T> operator -(const Vec3<T>& left)
{
  return Vec3<T>(-left.x, -left.y, -left.z);
}

template <typename T>
inline Vec3<T>& operator +=(Vec3<T>& left, const Vec3<T>& right)
{
  left.x += right.x;
  left.y += right.y;
  left.z += right.z;

  return left;
}

template <typename T>
inline Vec3<T>& operator -=(Vec3<T>& left, const Vec3<T>& right)
{
  left.x -= right.x;
  left.y -= right.y;
  left.z -= right.z;

  return left;
}

template <typename T>
inline Vec3<T> operator +(const Vec3<T>& left, const Vec3<T>& right)
{
  return Vec3<T>(left.x + right.x, left.y + right.y, left.z + right.z);
}

template <typename T>
inline Vec3<T> operator -(const Vec3<T>& left, const Vec3<T>& right)
{
  return Vec3<T>(left.x - right.x, left.y - right.y, left.z - right.z);
}

template <typename T>
inline Vec3<T> operator *(const Vec3<T>& left, T right)
{
  return Vec3<T>(left.x * right, left.y * right, left.z * right);
}

template <typename T>
inline Vec3<T> operator *(T left, const Vec3<T>& right)
{
  return Vec3<T>(right.x * left, right.y * left, right.z * left);
}

template <typename T>
inline Vec3<T>& operator *=(Vec3<T>& left, T right)
{
  left.x *= right;
  left.y *= right;
  left.z *= right;

  return left;
}

template <typename T>
inline Vec3<T> operator /(const Vec3<T>& left, T right)
{
  return Vec3<T>(left.x / right, left.y / right, left.z / right);
}

template <typename T>
inline Vec3<T>& operator /=(Vec3<T>& left, T right)
{
  left.x /= right;
  left.y /= right;
  left.z /= right;

  return left;
}

////////////////////////////////////////////////////////////

template <typename T>
inline bool operator ==(const Vec3<T>& left, const Vec3<T>& right)
{
  return (left.x == right.x) && (left.y == right.y) && (left.z == right.z);
}

template <typename T>
inline bool operator !=(const Vec3<T>& left, const Vec3<T>& right)
{
  return (left.x != right.x) || (left.y != right.y) || (left.z != right.z);
}

template <typename T>
inline bool operator <(const Vec3<T>& left, const Vec3<T>& right)
{
    return (left.x < right.x || left.y < right.y || left.z < right.z);
}

///////////////////////////////

template <typename T>
static T	length2(T x, T y, T z)
{
  return ( x * x + y * y + z * z );
}

template <typename T>
static T	length2(const Vec3<T>& v)
{
  return ( length2(v.x, v.y, v.z) );
}

template <typename T>
static T	length2(const Vec3<T>& v1, const Vec3<T>& v2)
{
  return ( length2(v2.x - v1.x, v2.y - v1.y, v2.z - v1.z) );
}

///////////////////////////////

template <typename T>
static T	length(T x, T y, T z)
{
  return ( fast_sqrt<T>( static_cast<T>(length2<T>(x, y, z)) ) );
}

template <typename T>
static T	length(const Vec3<T>& v)
{
  return ( length<T>(v.x, v.y, v.z) );
}

template <typename T>
static T	length(const Vec3<T>& v1, const Vec3<T>& v2)
{
  return ( length<T>(v2.x - v1.x, v2.y - v1.y, v2.z - v1.z) );
}

///////////////////////////////

template <typename T>
static void	normalize(Vec3<T>& v)
{
  v /= length<T>(v);
}

