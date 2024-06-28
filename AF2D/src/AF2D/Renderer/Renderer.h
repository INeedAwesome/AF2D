#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace AF {

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void Begin();
		static void End();

		static void Resize(int newWidth, int newHeight);
		static void SetScale(int scale);

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size);

	private:

	};

}
