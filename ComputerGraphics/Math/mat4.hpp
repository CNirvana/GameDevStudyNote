#pragma once

#include "vec3.hpp"

template<typename T>
struct Mat4x4
{
	T x[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
	Mat4x4() {}

	Mat4x4(T diagonal)
	{
		x[0][0] = x[1][1] = x[2][2] = x[3][3] = diagonal;
	}

	Mat4x4(T m00, T m01, T m02, T m03, T m10, T m11, T m12, T m13, T m20, T m21, T m22, T m23, T m30, T m31, T m32, T m33)
	{
		x[0][0] = m00;
		x[0][1] = m01;
		x[0][2] = m02;
		x[0][3] = m03;
		x[1][0] = m10;
		x[1][1] = m11;
		x[1][2] = m12;
		x[1][3] = m13;
		x[2][0] = m20;
		x[2][1] = m21;
		x[2][2] = m22;
		x[2][3] = m23;
		x[3][0] = m30;
		x[3][1] = m31;
		x[3][2] = m32;
		x[3][3] = m33;
	}

	const T* operator[] (size_t i) const { return x[i]; }
	T* operator[] (size_t i) { return x[i]; }

	Mat4x4 transpose() const
	{
		return Mat4x4(x[0][0], x[1][0], x[2][0], x[3][0],
					  x[0][1], x[1][1], x[2][1], x[3][1],
					  x[0][2], x[1][2], x[2][2], x[3][2],
					  x[0][3], x[1][3], x[2][3], x[3][3]);
	}

	Mat4x4& operator*=(const Mat4x4& other)
	{

	}

	Mat4x4 operator * (const Mat4x4& other)
	{

	}

	Vec3 operator*(const Vec3<T>& other)
	{

	}

	/*static Mat4x4 translate(const Vec3& translation);
	static Mat4x4 scale(const Vec3& scale);
	static Mat4x4 rotate(T angle, const Vec3& axis);
	static Mat4x4 rotateX(T angle);
	static Mat4x4 rotateY(T angle);
	static Mat4x4 rotateZ(T angle);*/
};

typedef Mat4x4<float> Mat4x4f;
typedef Mat4x4<int> Mat4x4i;