#pragma once

#include "common.h"

enum ECameraMovement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{
public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);

	glm::mat4 getViewMatrix() const { return glm::lookAt(m_Position, m_Position + m_Front, m_Up); }
	void processKeyboard(ECameraMovement direction, float deltaTime);
	void processMouseMovement(float xOffset, float yOffset);
	void processMouseScroll(float yOffset);

	float getZoom() const { return m_Zoom; }
	glm::vec3 getPosition() const { return m_Position; }
	glm::vec3 getFront() const { return m_Front; }

protected:
	void updateCameraVectors();

private:
	glm::vec3 m_Position;
	glm::vec3 m_Front;
	glm::vec3 m_Up;
	glm::vec3 m_Right;
	glm::vec3 m_WorldUp;

	float m_Yaw;
	float m_Pitch;
	float m_MoveSpeed;
	float m_MouseSensitivity;
	float m_Zoom;

};