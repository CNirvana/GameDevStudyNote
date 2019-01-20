#pragma once

#include "entity.h"

class Sphere : public Entity
{
public:
	Sphere(const Vec3f& position, float radius, Material* mat) : Entity(position, mat), m_Radius(radius) {}

	void setRadiuse(float radius) { m_Radius = radius; }
	float getRadiuse() const { return m_Radius; }

	virtual RaycastResult intersect(const Ray& ray) override
	{
		auto result = RaycastResult();

		Vec3f omc = ray.origin - m_Position;
		float DdotOmc = ray.direction.dot(omc);

		if (DdotOmc > 0)
		{
			return result;
		}

		float c = omc.dot(omc) - m_Radius * m_Radius;
		float root = DdotOmc * DdotOmc - c;

		if (root < 0)
		{
			return result;
		}

		result.hit = this;
		result.distance = -DdotOmc - sqrt(root);
		result.position = ray.getPoint(result.distance);
		result.normal = Vec3f::normalize(result.position - m_Position);

		return result;
	}

private:
	float m_Radius;

};