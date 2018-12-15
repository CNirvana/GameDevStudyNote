#pragma once

template<typename T>
inline Vec3<T>::Vec3() :
	x(0),
	y(0),
	z(0)
{
}

template<typename T>
inline Vec3<T>::Vec3(T _x, T _y, T _z) :
	x(_x),
	y(_y),
	z(_z)
{
}

template<typename T>
Vec3<T> operator - (const Vec3<T>& right)
{
	return Vec3<T>(-right.x, -right.y, -right.z);
}

template<typename T>
Vec3<T>& operator += (Vec3<T>& left, const Vec3<T>& right)
{
	left.x += right.x;
	left.y += right.y;
	left.z += right.z;
	return left;
}

template<typename T>
Vec3<T>& operator -= (Vec3<T>& left, const Vec3<T>& right)
{
	left.x -= right.x;
	left.y -= right.y;
	left.z -= right.z;
	return left;
}

template<typename T>
Vec3<T> operator + (const Vec3<T>& left, const Vec3<T>& right)
{
	return Vec3<T>(left.x + right.x, left.y + right.y, left.z + right.z);
}

template<typename T>
Vec3<T> operator - (const Vec3<T>& left, const Vec3<T>& right)
{
	return Vec3<T>(left.x - right.x, left.y - right.y, left.z - right.z);
}

template<typename T>
Vec3<T> operator * (const Vec3<T>& left, T right)
{
	return Vec3<T>(left.x * right, left.y * right, left.z * right);
}

template<typename T>
Vec3<T> operator * (T left, const Vec3<T>& right)
{
	return Vec3<T>(left * right.x, left * right.y, left * right.z);
}

template<typename T>
Vec3<T>& operator *= (Vec3<T>& left, T right)
{
	left.x *= right;
	left.y *= right;
	left.z *= right;
	return left;
}

template<typename T>
Vec3<T> operator / (const Vec3<T>& left, T right)
{
	// assert right != 0
	return Vec3<T>(left.x / right, left.y / right, left.z / right);
}

template<typename T>
Vec3<T>& operator /= (Vec3<T>& left, T right)
{
	left.x /= right;
	left.y /= right;
	left.z /= right;
	return left;
}

template<typename T>
bool operator == (const Vec3<T>& left, const Vec3<T>& right)
{
	return (left.x == right.x)
		&& (left.y == right.y)
		&& (left.z == right.z);
}

template<typename T>
bool operator != (const Vec3<T>& left, const Vec3<T>& right)
{
	return !(left == right);
}