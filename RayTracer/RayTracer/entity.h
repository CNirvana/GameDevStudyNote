#pragma once

#include "ray.h"
#include "material.h"

class Entity
{
public:
	Entity() : m_Position(0, 0, 0), m_Mat(nullptr) {}
	Entity(const Vec3f& position) : m_Position(position), m_Mat(nullptr) {}
	Entity(const Vec3f& position, Material* mat) : m_Position(position), m_Mat(mat) {}
	virtual ~Entity() { SAFE_DELETE(m_Mat); }

	void setPosition(const Vec3f& position) { m_Position = position; }
	Vec3f getPosition() const { return m_Position; }
	Material* getMaterial() const { return m_Mat; }

	virtual RaycastResult intersect(const Ray& ray) = 0;

protected:
	Vec3f m_Position;
	Material* m_Mat;

};