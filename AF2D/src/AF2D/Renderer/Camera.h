#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace AF {

	class Camera
	{
	public:
		Camera();
		~Camera() = default;

		void SetPosition(const glm::vec3 position);
		glm::vec3 GetPosition() const;

		void SetRotation(float rotation);
		float GetRotation() const;

	private:
		glm::vec3 m_Position;
		float m_Rotation; // Degrees
	};


}