


template <typename T>
inline Vec2<T>::Vec2()
  : x(0), y(0)
{

}

template <typename T>
inline Vec2<T>::Vec2(T X, T Y)
  : x(X), y(Y)
{

}

template <typename T>
template <typename U>
inline Vec2<T>::Vec2(const Vec2<U>& vector)
  : x(static_cast<T>(vector.x)),
    y(static_cast<T>(vector.y))
{
}

////////////////////////////////////////////////////////////

template <typename T>
inline Vec2<T> operator -(const Vec2<T>& right)
{
  return Vec2<T>(-right.x, -right.y);
}

template <typename T>
inline Vec2<T>& operator +=(Vec2<T>& left, const Vec2<T>& right)
{
  left.x += right.x;
  left.y += right.y;

  return left;
}

template <typename T>
inline Vec2<T>& operator -=(Vec2<T>& left, const Vec2<T>& right)
{
  left.x -= right.x;
  left.y -= right.y;

  return left;
}

template <typename T>
inline Vec2<T> operator +(const Vec2<T>& left, const Vec2<T>& right)
{
  return Vec2<T>(left.x + right.x, left.y + right.y);
}

template <typename T>
inline Vec2<T> operator -(const Vec2<T>& left, const Vec2<T>& right)
{
  return Vec2<T>(left.x - right.x, left.y - right.y);
}

template <typename T>
inline Vec2<T> operator *(const Vec2<T>& left, T right)
{
  return Vec2<T>(left.x * right, left.y * right);
}

template <typename T>
inline Vec2<T> operator *(T left, const Vec2<T>& right)
{
  return Vec2<T>(right.x * left, right.y * left);
}

template <typename T>
inline Vec2<T>& operator *=(Vec2<T>& left, T right)
{
  left.x *= right;
  left.y *= right;

  return left;
}

template <typename T>
inline Vec2<T> operator /(const Vec2<T>& left, T right)
{
  return Vec2<T>(left.x / right, left.y / right);
}

template <typename T>
inline Vec2<T>& operator /=(Vec2<T>& left, T right)
{
  left.x /= right;
  left.y /= right;

  return left;
}

////////////////////////////////////////////////////////////

template <typename T>
inline bool operator ==(const Vec2<T>& left, const Vec2<T>& right)
{
  return (left.x == right.x) && (left.y == right.y);
}

template <typename T>
inline bool operator !=(const Vec2<T>& left, const Vec2<T>& right)
{
  return (left.x != right.x) || (left.y != right.y);
}

////////////////////////////////////////////////////////////

template <typename T>
static T	length2(T x, T y)
{
  return ( x * x + y * y );
}

template <typename T>
static T	length2(const Vec2<T>& v)
{
  return ( length2(v.x, v.y) );
}

template <typename T>
static T	length2(const Vec2<T>& v1, const Vec2<T>& v2)
{
  return ( length2(v2.x - v1.x, v2.y - v1.y) );
}

////////////////////////////////////////////////////////////

template <typename T>
static T	length(T x, T y)
{
  return ( fast_sqrt<T>( static_cast<T>(length2<T>(x, y)) ) );
}

template <typename T>
static T	length(const Vec2<T>& v)
{
  return ( length<T>(v.x, v.y) );
}

template <typename T>
static T	length(const Vec2<T>& v1, const Vec2<T>& v2)
{
  return ( length<T>(v2.x - v1.x, v2.y - v1.y) );
}

////////////////////////////////////////////////////////////

template <typename T>
static void	normalize(Vec2<T>& v)
{
  v /= length<T>(v);
}

