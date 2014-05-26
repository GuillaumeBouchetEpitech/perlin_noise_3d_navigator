

template <typename T>
inline Vec4<T>::Vec4()
  : x(0), y(0), z(0), w(0)
{
}

template <typename T>
inline Vec4<T>::Vec4(T X, T Y, T Z, T W)
  : x(X), y(Y), z(Z), w(W)
{
}

template <typename T>
template <typename U>
inline Vec4<T>::Vec4(const Vec4<U>& vector)
  : x(static_cast<T>(vector.x)),
    y(static_cast<T>(vector.y)),
    z(static_cast<T>(vector.z)),
    w(static_cast<T>(vector.w))
{
}

////////////////////////////////////////////////////////////

template <typename T>
inline Vec4<T> operator -(const Vec4<T>& left)
{
  return Vec4<T>(-left.x, -left.y, -left.z, -left.w);
}

template <typename T>
inline Vec4<T>& operator +=(Vec4<T>& left, const Vec4<T>& right)
{
  left.x += right.x;
  left.y += right.y;
  left.z += right.z;
  left.w += right.w;

  return left;
}

template <typename T>
inline Vec4<T>& operator -=(Vec4<T>& left, const Vec4<T>& right)
{
  left.x -= right.x;
  left.y -= right.y;
  left.z -= right.z;
  left.w -= right.w;

  return left;
}

template <typename T>
inline Vec4<T> operator +(const Vec4<T>& left, const Vec4<T>& right)
{
  return Vec4<T>(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
}

template <typename T>
inline Vec4<T> operator -(const Vec4<T>& left, const Vec4<T>& right)
{
  return Vec4<T>(left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w);
}

template <typename T>
inline Vec4<T> operator *(const Vec4<T>& left, T right)
{
  return Vec4<T>(left.x * right, left.y * right, left.z * right, left.w * right);
}

template <typename T>
inline Vec4<T> operator *(T left, const Vec4<T>& right)
{
  return Vec4<T>(right.x * left, right.y * left, right.z * left, right.w * left);
}

template <typename T>
inline Vec4<T>& operator *=(Vec4<T>& left, T right)
{
  left.x *= right;
  left.y *= right;
  left.z *= right;
  left.w *= right;

  return left;
}

template <typename T>
inline Vec4<T> operator /(const Vec4<T>& left, T right)
{
  return Vec4<T>(left.x / right, left.y / right, left.z / right, left.w / right);
}

template <typename T>
inline Vec4<T>& operator /=(Vec4<T>& left, T right)
{
  left.x /= right;
  left.y /= right;
  left.z /= right;
  left.w /= right;

  return left;
}

////////////////////////////////////////////////////////////

template <typename T>
inline bool operator ==(const Vec4<T>& left, const Vec4<T>& right)
{
  return (left.x == right.x) && (left.y == right.y) && (left.z == right.z) && (left.w == right.w);
}

template <typename T>
inline bool operator !=(const Vec4<T>& left, const Vec4<T>& right)
{
  return (left.x != right.x) || (left.y != right.y) || (left.z != right.z) || (left.w != right.w);
}

template <typename T>
inline bool operator <(const Vec4<T>& left, const Vec4<T>& right)
{
    return (left.x < right.x || left.y < right.y || left.z < right.z || left.w < right.w);
}

///////////////////////////////

template <typename T>
static T	length2(T x, T y, T z, T w)
{
  return ( x * x + y * y + z * z + w * w );
}

template <typename T>
static T	length2(const Vec4<T>& v)
{
  return ( length2(v.x, v.y, v.z, v.w) );
}

template <typename T>
static T	length2(const Vec4<T>& v1, const Vec4<T>& v2)
{
  return ( length2(v2.x - v1.x, v2.y - v1.y, v2.z - v1.z, v2.w - v1.w) );
}

///////////////////////////////

template <typename T>
static T	length(T x, T y, T z, T w)
{
  return ( fast_sqrt<T>( static_cast<T>(length2<T>(x, y, z, w)) ) );
}

template <typename T>
static T	length(const Vec4<T>& v)
{
  return ( length<T>(v.x, v.y, v.z, v.w) );
}

template <typename T>
static T	length(const Vec4<T>& v1, const Vec4<T>& v2)
{
  return ( length<T>(v2.x - v1.x, v2.y - v1.y, v2.z - v1.z, v2.w - v1.w) );
}

///////////////////////////////

template <typename T>
static void	normalize(Vec4<T>& v)
{
  v /= length<T>(v);
}

