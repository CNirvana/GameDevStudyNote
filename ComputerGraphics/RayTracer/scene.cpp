#include "scene.h"

Scene::Scene(Camera* camera, int screenWidth, int screenHeight, const Color& backgroundColor)
	: m_Camera(camera), m_ScreenWidth(screenWidth), m_ScreenHeight(screenHeight), m_BackgroundColor(backgroundColor)
{
	m_Camera->setAspect((float)m_ScreenWidth / m_ScreenHeight);
	m_FrameBuffer = new FrameBuffer(m_ScreenWidth, m_ScreenHeight);
}

Scene::~Scene()
{
	for (size_t i = 0; i < m_Entities.size(); i++)
	{
		delete m_Entities[i];
	}
	m_Entities.clear();

	delete m_Camera;
	m_Camera = nullptr;

	delete m_FrameBuffer;
	m_FrameBuffer = nullptr;
}

void Scene::addEntity(Entity* entity)
{
	m_Entities.push_back(entity);
}

void Scene::render()
{
	m_FrameBuffer->clear(m_BackgroundColor);

	for (int y = 0; y < m_ScreenHeight; y++)
	{
		float sy = 1 - (float)y / m_ScreenHeight;
		for (int x = 0; x < m_ScreenWidth; x++)
		{
			float sx = (float)x / m_ScreenWidth;

			Ray ray = m_Camera->screenPointToRay(sx, sy);
			Color color = rayTrace(ray);
			m_FrameBuffer->setPixel(x, y, color);
		}
	}

	m_FrameBuffer->flush();
}

Color Scene::rayTrace(const Ray& ray)
{
	float minDistance = std::numeric_limits<float>::max();
	RaycastResult minRes;

	for (size_t i = 0; i < m_Entities.size(); i++)
	{
		RaycastResult res = m_Entities[i]->intersect(ray);
		if (res.hit != nullptr && res.distance < minDistance)
		{
			minDistance = res.distance;
			minRes = res;
		}
	}

	if (minRes.hit != nullptr)
	{
		FragInput input;
		input.position = minRes.position;
		input.normal = minRes.normal;
		input.viewDir = -ray.direction;
		input.lightDir = Vec3f(1.0f, 1.0f, 1.0f);
		input.lightColor = Color::white;
		return minRes.hit->getMaterial()->sample(input);
	}
	else
	{
		return m_BackgroundColor;
	}
}