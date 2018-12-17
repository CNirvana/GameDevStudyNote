template<typename T>
inline Vec2<T>::Vec2() :
x(0), 
y(0)
{
}

template<typename T>
inline Vec2<T>::Vec2(T _x, T _y) :
x(_x),
y(_y)
{
}

template<typename T>
Vec2<T> operator - (const Vec2<T>& right)
{
	return Vec2<T>(-right.x, -right.y);
}

template<typename T>
Vec2<T>& operator += (Vec2<T>& left, const Vec2<T>& right)
{
	left.x += right.x;
	left.y += right.y;
	return left;
}

template<typename T>
Vec2<T>& operator -= (Vec2<T>& left, const Vec2<T>& right)
{
	left.x -= right.x;
	left.y -= right.y;
	return left;
}

template<typename T>
Vec2<T> operator + (const Vec2<T>& left, const Vec2<T>& right)
{
	return Vec2<T>(left.x + right.x, left.y + right.y);
}

template<typename T>
Vec2<T> operator - (const Vec2<T>& left, const Vec2<T>& right)
{
	return Vec2<T>(left.x - right.x, left.y - right.y);
}

template<typename T>
Vec2<T> operator * (const Vec2<T>& left, T right)
{
	return Vec2<T>(left.x * right, left.y * right);
}

template<typename T>
Vec2<T> operator * (T left, const Vec2<T>& right)
{
	return Vec2<T>(left * right.x, left * right.y);
}

template<typename T>
Vec2<T>& operator *= (Vec2<T>& left, T right)
{
	left.x *= right;
	left.y *= right;
	return left;
}

template<typename T>
Vec2<T> operator / (const Vec2<T>& left, T right)
{
	// assert right != 0
	return Vec2<T>(left.x / right, left.y / right);
}

template<typename T>
Vec2<T>& operator /= (Vec2<T>& left, T right)
{
	left.x /= right;
	left.y /= right;
	return left;
}

template<typename T>
bool operator == (const Vec2<T>& left, const Vec2<T>& right)
{
	return (left.x == right.x)
		&& (left.y == right.y);
}

template<typename T>
bool operator != (const Vec2<T>& left, const Vec2<T>& right)
{
	return !(left == right);
}