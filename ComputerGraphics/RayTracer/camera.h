#pragma once

#include "vec3.hpp"
#include "ray.h"

class Camera
{
public:
	Camera(const Vec3f& position, const Vec3f& front, const Vec3f& up, float fov, float aspect)
		: m_Position(position), m_Front(Vec3f::normalize(front)), m_Fov(fov), m_Aspect(aspect)
	{
		Vec3f u = Vec3f::normalize(up);
		m_right = m_Front.cross(up);
		m_Up = m_right.cross(m_Front);
		recalculateFovScale();
	}

	Ray screenPointToRay(float x, float y) const
	{
		Vec3f r = m_right * ((2 * x - 1) * m_FovScale);
		Vec3f u = m_Up * ((2 * y - 1) * m_FovScale / m_Aspect);
		return Ray(m_Position, Vec3f::normalize(m_Front + r + u));
	}

	float getAspect() const { return m_Aspect; }
	void setAspect(float aspect) { m_Aspect = aspect; }
	float getFov() const { return m_Fov; }
	void setFov(float fov)
	{
		m_Fov = fov;
		recalculateFovScale();
	}

private:
	void recalculateFovScale() { m_FovScale = std::tan(m_Fov * 0.5f * 3.141592654f / 180.0f); }

	Vec3f m_Position;
	Vec3f m_Front;
	Vec3f m_Up;
	Vec3f m_right;
	float m_Fov;
	float m_FovScale;
	float m_Aspect;

};