#include "afpch.h"
#include "Texture2D.h"

#include <glad/glad.h>
#include <stb/stb_image.h>

namespace AF {

	Texture2D::~Texture2D()
	{

	}

	void Texture2D::Init(const std::string& filepath, TextureScaling scaling)
	{
		int width, height, channels;
		TextureBuffer buffer{};

		stbi_set_flip_vertically_on_load(true);
		buffer.m_Data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
		buffer.m_Width = width;
		buffer.m_Height = height;
		buffer.m_Components = channels;

		Init(buffer, scaling);

		stbi_image_free(buffer.m_Data);

	}
	
	void Texture2D::Init(const TextureBuffer& buffer, TextureScaling scaling)
	{
		int format = GL_RED;
		if (buffer.m_Components == 1)
			format = GL_RED;
		else if (buffer.m_Components == 2)
			format = GL_RG;
		else if (buffer.m_Components == 3)
			format = GL_RGB;
		else if (buffer.m_Components == 4)
			format = GL_RGBA;
		else {
			std::cout << "Unsupported texture! Number of texture channels exceeded 4! " << std::endl;
			__debugbreak();
			return;
		}

		int glScale = scaling == TextureScaling::NEAREST ? GL_NEAREST : GL_LINEAR;
		
		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glTexImage2D(GL_TEXTURE_2D, 0, format, buffer.m_Width, buffer.m_Height, 0, format, GL_UNSIGNED_BYTE, buffer.m_Data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, glScale);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, glScale);
		glGenerateMipmap(GL_TEXTURE_2D);

		m_Width = buffer.m_Width;
		m_Height = buffer.m_Height;
	}
	
	void Texture2D::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}
	
	void Texture2D::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}
