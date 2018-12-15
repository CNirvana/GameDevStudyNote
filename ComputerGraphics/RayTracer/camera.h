#pragma once

#include "vec3.hpp"
#include "utility.h"
#include "ray.h"

class Camera
{
public:
	Camera(const Vec3f& position, const Vec3f& front, const Vec3f& up, float fov, float aspect);

	Ray screenPointToRay(float x, float y) const;

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