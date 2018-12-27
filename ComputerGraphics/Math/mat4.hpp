#pragma once

#include "vec3.hpp"
#include "vec4.hpp"

struct Mat4x4
{
	float m[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
	Mat4x4() {}

	Mat4x4(float diagonal)
	{
		m[0][0] = m[1][1] = m[2][2] = m[3][3] = diagonal;
	}

	Mat4x4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33)
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

	const float* operator[] (size_t i) const { return m[i]; }
	float* operator[] (size_t i) { return m[i]; }

	Mat4x4 transpose() const
	{
		return Mat4x4(m[0][0], m[1][0], m[2][0], m[3][0],
					  m[0][1], m[1][1], m[2][1], m[3][1],
					  m[0][2], m[1][2], m[2][2], m[3][2],
					  m[0][3], m[1][3], m[2][3], m[3][3]);
	}

	static Mat4x4 perspective(float fov, float aspect, float near, float far)
	{
		Mat4x4 mat;
		float c = 1 / std::tan(fov * 0.5);
		mat.m[0][0] = c / aspect;
		mat.m[1][1] = c;
		mat.m[2][2] = far / (near - far);
		mat.m[2][3] = far * near / (near - far);
		mat.m[3][2] = -1;
		mat.m[3][3] = 0;

		return mat;
	}

	static Mat4x4 lookAt(const Vec3f& eye, const Vec3f& center, const Vec3f& up)
	{
		Vec3f f = Vec3f::normalize(center - eye);
		Vec3f r = Vec3f::normalize(Vec3f::cross(f, up));
		Vec3f u = Vec3f::cross(r, f);

		Mat4x4 m(1.0f);
		m[0][0] = r.x;
		m[1][0] = u.x;
		m[2][0] = -f.x;

		m[0][1] = r.y;
		m[1][1] = u.y;
		m[2][1] = -f.y;

		m[0][2] = r.z;
		m[1][2] = u.z;
		m[2][2] = -f.z;

		m[0][3] = -Vec3f::dot(r, eye);
		m[1][3] = -Vec3f::dot(u, eye);
		m[2][3] = Vec3f::dot(f, eye);

		return m;
	}

	Mat4x4 operator * (const Mat4x4& other)
	{
		Mat4x4 res;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				res[i][j] = m[i][0] * other.m[0][j]
					+ m[i][1] * other.m[1][j]
					+ m[i][2] * other.m[2][j]
					+ m[i][3] * other.m[3][j];
			}
		}

		return res;
	}

	Vec4<float> operator * (const Vec4f& other) const
	{
		float x = m[0][0] * other.x + m[0][1] * other.y + m[0][2] * other.z + m[0][3] * other.w;
		float y = m[1][0] * other.x + m[1][1] * other.y + m[1][2] * other.z + m[1][3] * other.w;
		float z = m[2][0] * other.x + m[2][1] * other.y + m[2][2] * other.z + m[2][3] * other.w;
		float w = m[3][0] * other.x + m[3][1] * other.y + m[3][2] * other.z + m[3][3] * other.w;

		return Vec4<float>(x, y, z, w);
	}

	Vec3<float> operator*(const Vec3f& other) const
	{
		float x = m[0][0] * other.x + m[0][1] * other.y + m[0][2] * other.z + m[0][3];
		float y = m[1][0] * other.x + m[1][1] * other.y + m[1][2] * other.z + m[1][3];
		float z = m[2][0] * other.x + m[2][1] * other.y + m[2][2] * other.z + m[2][3];
		float w = m[3][0] * other.x + m[3][1] * other.y + m[3][2] * other.z + m[3][3];

		if (w != 1)
		{
			float invw = 1 / w;
			return Vec3f(x * invw, y * invw, z * invw);
		}
		else
		{
			return Vec3f(x, y, z);
		}
	}

	static Mat4x4 translate(const Vec3f& translation)
	{
		Mat4x4 mat(1.0f);
		mat[0][3] = translation.x;
		mat[1][3] = translation.y;
		mat[2][3] = translation.z;
		return mat;
	}

	static Mat4x4 scale(float s)
	{
		Mat4x4 mat(s);
		mat[3][3] = 1;
		return mat;
	}

	static Mat4x4 scale(const Vec3f& s)
	{
		Mat4x4 mat;
		mat[0][0] = s.x;
		mat[1][1] = s.y;
		mat[2][2] = s.z;
		mat[3][3] = 1.0f;
		return mat;
	}

	/*
	static Mat4x4 rotate(float angle, const Vec3& axis);
	static Mat4x4 rotateX(float angle);
	static Mat4x4 rotateY(float angle);
	static Mat4x4 rotateZ(float angle);*/
};