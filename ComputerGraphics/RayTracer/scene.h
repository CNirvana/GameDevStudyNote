#pragma once

#include <vector>
#include "entity.h"
#include "camera.h"
#include "frame_buffer.h"

class Scene
{
public:
	Scene(Camera* camera, int screenWidth, int screenHeight, const Color& backgroundColor);
	~Scene();

	void addEntity(Entity* entity);
	void render();

protected:
	Color rayTrace(const Ray& ray);

private:
	Camera* m_Camera;
	FrameBuffer* m_FrameBuffer;

	std::vector<Entity*> m_Entities;
	int m_ScreenWidth;
	int m_ScreenHeight;
	Color m_BackgroundColor;
};