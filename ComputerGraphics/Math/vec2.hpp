#pragma once

template<typename T>
struct Vec2
{
	T x;
	T y;

	Vec2();
	Vec2(T _x, T _y);
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