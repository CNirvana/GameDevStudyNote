#pragma once

#include "vec3.hpp"
#include "vec4.hpp"

template<typename T>
struct Mat4x4
{
	T m[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
	Mat4x4() {}

	Mat4x4(T diagonal)
	{
		m[0][0] = m[1][1] = m[2][2] = m[3][3] = diagonal;
	}

	Mat4x4(T m00, T m01, T m02, T m03, T m10, T m11, T m12, T m13, T m20, T m21, T m22, T m23, T m30, T m31, T m32, T m33)
	{
		m[0][0] = m00;
		m[0][1] = m01;
		m[0][2] = m02;
		m[0][3] = m03;
		m[1][0] = m10;
		m[1][1] = m11;
		m[1][2] = m12;
		m[1][3] = m13;
		m[2][0] = m20;
		m[2][1] = m21;
		m[2][2] = m22;
		m[2][3] = m23;
		m[3][0] = m30;
		m[3][1] = m31;
		m[3][2] = m32;
		m[3][3] = m33;
	}

	const T* operator[] (size_t i) const { return m[i]; }
	T* operator[] (size_t i) { return m[i]; }

	Mat4x4 transpose() const
	{
		return Mat4x4(m[0][0], m[1][0], m[2][0], m[3][0],
					  m[0][1], m[1][1], m[2][1], m[3][1],
					  m[0][2], m[1][2], m[2][2], m[3][2],
					  m[0][3], m[1][3], m[2][3], m[3][3]);
	}

	static Mat4x4 perspective(T fov, T aspect, T near, T far)
	{
		Mat4x4 mat;
		T c = 1 / std::tan(fov * 0.5);
		mat.m[0][0] = c / aspect;
		mat.m[1][1] = c;
		mat.m[2][2] = far / (near - far);
		mat.m[2][3] = far * near / (near - far);
		mat.m[3][2] = -1;
		mat.m[3][3] = 0;

		return mat;
	}

	Mat4x4& operator*=(const Mat4x4& other)
	{

	}

	Mat4x4 operator * (const Mat4x4& other)
	{
	}

	Vec4<T> operator * (const Vec4<T>& other)
	{
		T x = m[0][0] * other.x + m[0][1] * other.y + m[0][2] * other.z + m[0][3] * other.w;
		T y = m[1][0] * other.x + m[1][1] * other.y + m[1][2] * other.z + m[1][3] * other.w;
		T z = m[2][0] * other.x + m[2][1] * other.y + m[2][2] * other.z + m[2][3] * other.w;
		T w = m[3][0] * other.x + m[3][1] * other.y + m[3][2] * other.z + m[3][3] * other.w;

		return Vec4<T>(x, y, z, w);
	}

	Vec3<T> operator*(const Vec3<T>& other)
	{
		T x = m[0][0] * other.x + m[0][1] * other.y + m[0][2] * other.z + m[0][3];
		T y = m[1][0] * other.x + m[1][1] * other.y + m[1][2] * other.z + m[1][3];
		T z = m[2][0] * other.x + m[2][1] * other.y + m[2][2] * other.z + m[2][3];
		T w = m[3][0] * other.x + m[3][1] * other.y + m[3][2] * other.z + m[3][3];

		if (w != 1)
		{
			T invw = 1 / w;
			return Vec3(x * invw, y * invw, z * invw);
		}
		else
		{
			return Vec3(x, y, z);
		}
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