#include "camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
: m_Position(position), m_WorldUp(up), m_Front(0.0f, 0.0f, -1.0f), m_Yaw(yaw), m_Pitch(pitch), m_MoveSpeed(2.5f), m_MouseSensitivity(0.1f), m_Zoom(45.0f)
{
    updateCameraVectors();
}

void Camera::updateCameraVectors()
{
    glm::vec3 front = glm::vec3(1.0f);
    front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    front.y = sin(glm::radians(m_Pitch));
    front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Front = glm::normalize(front);
    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}

void Camera::processKeyboard(ECameraMovement direction, float deltaTime)
{
    float velocity = m_MoveSpeed * deltaTime;
    if (direction == FORWARD) m_Position += m_Front * velocity;
    if (direction == BACKWARD) m_Position -= m_Front * velocity;
    if (direction == LEFT) m_Position -= m_Right * velocity;
    if (direction == RIGHT) m_Position += m_Right * velocity;
}

void Camera::processMouseMovement(float xOffset, float yOffset)
{
    xOffset *= m_MouseSensitivity;
    yOffset *= m_MouseSensitivity;
    m_Yaw += xOffset;
    m_Pitch += yOffset;

    if (m_Pitch > 89.0f) m_Pitch = 89.0f;
    if (m_Pitch < -89.0f) m_Pitch = -89.0f;

    updateCameraVectors();
}

void Camera::processMouseScroll(float yOffset)
{
    if (m_Zoom >= 1.0f && m_Zoom <= 45.0f) m_Zoom -= yOffset;
    if (m_Zoom <= 1.0f) m_Zoom = 1.0f;
    if (m_Zoom >= 45.0f) m_Zoom = 45.0f;
}