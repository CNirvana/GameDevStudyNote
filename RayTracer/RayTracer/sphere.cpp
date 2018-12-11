#include <cmath>
#include "sphere.h"

RaycastResult Sphere::intersect(const Ray& ray)
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
	result.normal = (result.position - m_Position).normalize();

	return result;
}