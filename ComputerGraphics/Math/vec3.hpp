#pragma once

#include <cmath>
#include <iostream>

template<typename T>
struct Vec3
{
	T x;
	T y;
	T z;

	Vec3();
	Vec3(T _x, T _y, T _z);

	inline T magnitude() const
	{
		return std::sqrt(x * x + y * y + z * z);
	}

	inline T sqrMagnitude() const
	{
		return x * x + y * y + z * z;
	}

	inline Vec3 normalize() const
	{
		T len = magnitude();
		if (len == 0)
		{
			return *this;
		}

		T invLen = 1 / len;
		return Vec3(x * invLen, y * invLen, z * invLen);
	}

	inline T dot(const Vec3& other) const
	{
		return x * other.x + y * other.y + z * other.z;
	}

	inline Vec3 cross(const Vec3& other) const
	{
		return Vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
	}

	inline T distance(const Vec3& other) const
	{
		T a = (x - other.x);
		T b = (y - other.y);
		T c = (z - other.z);
		return sqrt(a * a + b * b + c * c);
	}

	inline static T dot(const Vec3& left, const Vec3& right)
	{
		return left.x * right.x + left.y * right.y + left.z * right.z;
	}

	inline static Vec3 cross(const Vec3& left, const Vec3& right)
	{
		return Vec3(left.y * right.z - left.z * right.y,
			left.z * right.x - left.x * right.z,
			left.x * right.y - left.y * right.x);
	}

	inline static void normalize(Vec3& v)
	{
		T len = v.magnitude();
		if (len == 0)
		{
			return;
		}

		T invLen = 1 / len;
		v = v * invLen;
	}

	friend std::ostream& operator << (std::ostream& s, const Vec3<T>& v)
	{
		return s << '(' << v.x << ", " << v.y << ", " << v.z << ')';
	}
};

template<typename T>
Vec3<T> operator - (const Vec3<T>& right);

template<typename T>
Vec3<T>& operator += (Vec3<T>& left, const Vec3<T>& right);

template<typename T>
Vec3<T>& operator -= (Vec3<T>& left, const Vec3<T>& right);

template<typename T>
Vec3<T> operator + (const Vec3<T>& left, const Vec3<T>& right);

template<typename T>
Vec3<T> operator - (const Vec3<T>& left, const Vec3<T>& right);

template<typename T>
Vec3<T> operator * (const Vec3<T>& left, T right);

template<typename T>
Vec3<T> operator * (T left, const Vec3<T>& right);

template<typename T>
Vec3<T>& operator *= (const Vec3<T>& left, T right);

template<typename T>
Vec3<T> operator / (const Vec3<T>& left, T right);

template<typename T>
Vec3<T>& operator /= (Vec3<T>& left, T right);

template<typename T>
bool operator == (const Vec3<T>& left, const Vec3<T>& right);

template<typename T>
bool operator != (const Vec3<T>& left, const Vec3<T>& right);

#include "vec3.inl"

typedef Vec3<int> Vec3i;
typedef Vec3<float> Vec3f;