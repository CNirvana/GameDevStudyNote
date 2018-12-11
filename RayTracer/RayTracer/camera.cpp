#include "camera.h"

Camera::Camera(const Vec3f& position, const Vec3f& front, const Vec3f& up, float fov, float aspect)
	: m_Position(position), m_Front(front), m_Fov(fov), m_Aspect(aspect)
{
	m_right = m_Front.cross(up);
	m_Up = m_right.cross(m_Front);
	recalculateFovScale();
}

Ray Camera::screenPointToRay(float x, float y) const
{
	Vec3f r = m_right * ((2 * x - 1) * m_FovScale);
	Vec3f u = m_Up * ((2 * y - 1) * m_FovScale / m_Aspect);
	return Ray(m_Position, (m_Front + r + u).normalize());
}