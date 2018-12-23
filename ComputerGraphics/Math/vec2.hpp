#pragma once

#include <cmath>
#include <iostream>

template<typename T>
struct Vec2
{
	
	union
	{
		struct
		{
			T x;
			T y;
		};
		T raw[2];
	};

	Vec2();
	Vec2(T _x, T _y);

	inline T magnitude() const
	{
		return std::sqrt(sqrMagnitude());
	}

	inline T sqrMagnitude() const
	{
		return x * x + y * y;
	}

	inline void normalize() const
	{
		T len = magnitude();
		if(len == 0)
		{
			return;
		}

		T invLen = 1 / len;
		x *= invLen;
		y *= invLen;;
	}

	inline T dot(const Vec2& other) const
	{
		return x * other.x + y * other.y;
	}

	inline T determinant(const Vec2& right) const
	{
		return x * right.y - y * right.x;
	}

	inline T distance(const Vec2& other) const
	{
		T a = (x - other.x);
		T b = (y - other.y);
		return std::sqrt(a * a + b * b);
	}

	inline static T dot(const Vec2& left, const Vec2& right)
	{
		return left.dot(right);
	}

	inline static T determinant(const Vec2& left, const Vec2& right)
	{
		return left.determinant(right);
	}

	inline static Vec2 normalize(const Vec2& v)
	{
		T len = v.magnitude();
		if (len == 0)
		{
			return v;
		}

		T invLen = 1 / len;
		return v * invLen;
	}

	friend std::ostream& operator << (std::ostream& s, const Vec2<T>& v)
	{
		return s << '(' << v.x << ", " << v.y << ')';
	}
};

template<typename T>
Vec2<T> operator - (const Vec2<T>& right);

template<typename T>
Vec2<T>& operator += (Vec2<T>& left, const Vec2<T>& right);

template<typename T>
Vec2<T>& operator -= (Vec2<T>& left, const Vec2<T>& right);

template<typename T>
Vec2<T> operator + (const Vec2<T>& left, const Vec2<T>& right);

template<typename T>
Vec2<T> operator - (const Vec2<T>& left, const Vec2<T>& right);

template<typename T>
Vec2<T> operator * (const Vec2<T>& left, T right);

template<typename T>
Vec2<T> operator * (T left, const Vec2<T>& right);

template<typename T>
Vec2<T>& operator *= (const Vec2<T>& left, T right);

template<typename T>
Vec2<T> operator / (const Vec2<T>& left, T right);

template<typename T>
Vec2<T>& operator /= (Vec2<T>& left, T right);

template<typename T>
bool operator == (const Vec2<T>& left, const Vec2<T>& right);

template<typename T>
bool operator != (const Vec2<T>& left, const Vec2<T>& right);

#include "vec2.inl"

typedef Vec2<int> Vec2i;
typedef Vec2<float> Vec2f;