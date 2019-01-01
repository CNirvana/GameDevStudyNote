#pragma once

template<typename T>
inline Vec4<T>::Vec4() :
	x(0),
	y(0),
	z(0),
    w(0)
{
}

template<typename T>
inline Vec4<T>::Vec4(T _x, T _y, T _z, T _w) :
	x(_x),
	y(_y),
	z(_z),
    w(_w)
{
}

template<typename T>
Vec4<T> operator - (const Vec4<T>& right)
{
	return Vec4<T>(-right.x, -right.y, -right.z, -right.w);
}

template<typename T>
Vec4<T>& operator += (Vec4<T>& left, const Vec4<T>& right)
{
	left.x += right.x;
	left.y += right.y;
	left.z += right.z;
    left.w += right.w;
	return left;
}

template<typename T>
Vec4<T>& operator -= (Vec4<T>& left, const Vec4<T>& right)
{
	left.x -= right.x;
	left.y -= right.y;
	left.z -= right.z;
    left.w -= right.w;
	return left;
}

template<typename T>
Vec4<T> operator + (const Vec4<T>& left, const Vec4<T>& right)
{
	return Vec4<T>(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
}

template<typename T>
Vec4<T> operator - (const Vec4<T>& left, const Vec4<T>& right)
{
	return Vec4<T>(left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w);
}

template<typename T>
Vec4<T> operator * (const Vec4<T>& left, T right)
{
	return Vec4<T>(left.x * right, left.y * right, left.z * right, left.w * right);
}

template<typename T>
Vec4<T> operator * (T left, const Vec4<T>& right)
{
	return right * left;
}

template<typename T>
Vec4<T>& operator *= (Vec4<T>& left, T right)
{
	left.x *= right;
	left.y *= right;
	left.z *= right;
    left.w *= right;
	return left;
}

template<typename T>
T operator * (const Vec4<T>& left, const Vec4<T>& right)
{
	return left.dot(right);
}

template<typename T>
Vec4<T> operator / (const Vec4<T>& left, T right)
{
	// assert right != 0
	return Vec4<T>(left.x / right, left.y / right, left.z / right, left.w / right);
}

template<typename T>
Vec4<T>& operator /= (Vec4<T>& left, T right)
{
	left.x /= right;
	left.y /= right;
	left.z /= right;
    left.w /= right;
	return left;
}

template<typename T>
bool operator == (const Vec4<T>& left, const Vec4<T>& right)
{
	return (left.x == right.x)
		&& (left.y == right.y)
		&& (left.z == right.z)
        && (left.w == right.w);
}

template<typename T>
bool operator != (const Vec4<T>& left, const Vec4<T>& right)
{
	return !(left == right);
}