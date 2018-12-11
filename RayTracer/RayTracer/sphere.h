#pragma once

#include "entity.h"

class Sphere : public Entity
{
public:
	Sphere(const Vec3f& position, float radius, Material* mat) : Entity(position, mat), m_Radius(radius) {}

	void setRadiuse(float radius) { m_Radius = radius; }
	float getRadiuse() const { return m_Radius; }

	virtual RaycastResult intersect(const Ray& ray) override;

private:
	float m_Radius;

};