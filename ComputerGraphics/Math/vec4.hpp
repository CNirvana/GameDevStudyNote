#pragma once

#include <cmath>
#include <iostream>

template<typename T>
struct Vec4
{
	
	union
	{
		struct
		{
			T x;
			T y;
			T z;
			T w;
		};
		T raw[4];
	};

	Vec4();
	Vec4(T _x, T _y, T _z, T _w);

	inline T magnitude() const
	{
		return std::sqrt(sqrMagnitude());
	}

	inline T sqrMagnitude() const
	{
		return x * x + y * y + z * z + w * w;
	}

	inline void normalize() const
	{
		T len = magnitude();
		if (len == 0)
		{
			return;
		}

		T invLen = (float)1 / len;
		x *= invLen;
		y *= invLen;
		z *= invLen;
		w *= invLen;
	}

	inline T dot(const Vec4& other) const
	{
		return x * other.x + y * other.y + z * other.z + w * other.w;
	}

	inline static T dot(const Vec4& left, const Vec4& right)
	{
		return left.dot(right);
	}

	inline static Vec4 normalize(const Vec4& v)
	{
		T len = v.magnitude();
		if (len == 0)
		{
			return v;
		}

		T invLen = (float)1 / len;
		return v * invLen;
	}

	friend std::ostream& operator << (std::ostream& s, const Vec4<T>& v)
	{
		return s << '(' << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ')';
	}
};

template<typename T>
Vec4<T> operator - (const Vec4<T>& right);

template<typename T>
Vec4<T>& operator += (Vec4<T>& left, const Vec4<T>& right);

template<typename T>
Vec4<T>& operator -= (Vec4<T>& left, const Vec4<T>& right);

template<typename T>
Vec4<T> operator + (const Vec4<T>& left, const Vec4<T>& right);

template<typename T>
Vec4<T> operator - (const Vec4<T>& left, const Vec4<T>& right);

template<typename T>
Vec4<T> operator * (const Vec4<T>& left, T right);

template<typename T>
Vec4<T> operator * (T left, const Vec4<T>& right);

template<typename T>
Vec4<T>& operator *= (const Vec4<T>& left, T right);

template<typename T>
T operator * (const Vec4<T>& left, const Vec4<T>& right);

template<typename T>
Vec4<T> operator / (const Vec4<T>& left, T right);

template<typename T>
Vec4<T>& operator /= (Vec4<T>& left, T right);

template<typename T>
bool operator == (const Vec4<T>& left, const Vec4<T>& right);

template<typename T>
bool operator != (const Vec4<T>& left, const Vec4<T>& right);

#include "vec4.inl"

typedef Vec4<int> Vec4i;
typedef Vec4<float> Vec4f;