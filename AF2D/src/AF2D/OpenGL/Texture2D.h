#pragma once

#include "AF2D/Buffer.h"

namespace AF {

	class Texture2D
	{
	public:

		enum TextureScaling {
			LINEAR,
			NEAREST
		};

		Texture2D() = default;
		~Texture2D();

		void Init(const std::string& filepath, TextureScaling scaling = LINEAR);
		void Init(const TextureBuffer& buffer, TextureScaling scaling);

		void Bind();
		void Unbind();

		unsigned int GetWidth() const { return m_Width; }
		unsigned int GetHeight() const { return m_Height; }

	private:
		unsigned int m_TextureID;
		unsigned int m_Width;
		unsigned int m_Height;
	};

}


