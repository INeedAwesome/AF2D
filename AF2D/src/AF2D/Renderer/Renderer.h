#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "AF2D/OpenGL/Texture2D.h"

namespace AF {

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void Begin();
		static void End();

		/*!
		* @brief Allow the renderer to render to the specified width and height
		*/
		static void Resize(int newWidth, int newHeight);

		/*!
		* @brief Set the scale of a 1 by 1 block, for example - a scale of 32 would mean a one-by-one block covers one 1/32 of the height
		*/
		static void SetScale(int scale);

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, Texture2D& texture);

	private:

	};

}
