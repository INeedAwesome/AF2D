#include "afpch.h"
#include "Camera.h"

namespace AF {
	
	Camera::Camera()
		: m_Position(0, 0, 0), m_Rotation(0)
	{
	}

	void Camera::SetPosition(const glm::vec3 position)
	{
		m_Position = position;
	}

	glm::vec3 Camera::GetPosition() const
	{
		return m_Position;
	}

	void Camera::SetRotation(float rotation)
	{
		m_Rotation = rotation;
	}

	float Camera::GetRotation() const
	{
		return m_Rotation;
	}

}