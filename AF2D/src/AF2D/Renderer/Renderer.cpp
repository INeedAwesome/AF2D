#include "afpch.h"
#include "Renderer.h"

#include <string>

#include "AF2D/OpenGL/Shader.h"
#include "AF2D/OpenGL/VertexArray.h"
#include "AF2D/OpenGL/Texture2D.h"

#include <glad/glad.h>

namespace AF {

	struct RendererData {
		vertexArray vertexArray;
		Shader shader;
		Texture2D whiteTexture;

		unsigned int Width;
		unsigned int Height;
		int Scale;

	};

	static float verticesData[] = {
		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,		1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,		1.0f, 1.0f,
		0.0f, 1.0f, 0.0f,		0.0f, 1.0f
	};

	static unsigned int elements[] = {
		0, 1, 2, 0, 2, 3
	};

	static RendererData* s_Data;

	void Renderer::Init()
	{
		s_Data = new RendererData();

		s_Data->vertexArray.Init(verticesData, _countof(verticesData), elements, _countof(elements));

		std::string vertexShaderSource = R"""(#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 oTexCoords;

uniform mat4 transform;
uniform mat4 view;

void main()
{
	gl_Position = view * transform * vec4(aPos, 1.0);
	oTexCoords = aTexCoords;
}
)""";

		std::string fragmentShaderSource = R"""(#version 330 core
out vec4 FragColor;
in vec2 oTexCoords;

uniform sampler2D boundTexture;

void main()
{
	//FragColor = vec4(oTexCoords.x, oTexCoords.y, 0.0f, 1.0f);
	FragColor = texture(boundTexture, oTexCoords);
	if (FragColor.a < 0.1)
	{
		discard;
	}
} 
)""";
		s_Data->shader.Init(vertexShaderSource, fragmentShaderSource);
		glm::mat4 view = glm::ortho(0.0f, ((float)s_Data->Width / (float)s_Data->Height) * (float)s_Data->Scale, 0.0f, (float)s_Data->Scale, -100.0f, 100.0f);
		s_Data->shader.SetUniform("view", view);

		unsigned char* data = new unsigned char[3];
		data[0] = 255; data[1] = 255; data[2] = 255;
		TextureBuffer buffer{data, 1, 1, 3};
		s_Data->whiteTexture.Init(buffer, Texture2D::LINEAR);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
	}

	void Renderer::Shutdown()
	{
	}

	void Renderer::Begin()
	{
		glClearColor(0.2f, 0.4f, 1.0f, 1.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	}

	void Renderer::End()
	{
	}

	void Renderer::Resize(int newWidth, int newHeight)
	{
		glViewport(0, 0, newWidth, newHeight);
		s_Data->Width = newWidth;
		s_Data->Height= newHeight;

		glm::mat4 view = glm::ortho(0.0f, ((float)s_Data->Width / (float)s_Data->Height) * (float)s_Data->Scale, 0.0f, (float)s_Data->Scale, -100.0f, 100.0f);
		s_Data->shader.SetUniform("view", view);
	}

	void Renderer::SetScale(int scale)
	{
		s_Data->Scale = scale;
	}

	void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& size)
	{
		s_Data->shader.Bind();

		s_Data->whiteTexture.Bind();
		
		glm::mat4 transform = // TRS - transformation rotation scale
			glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f }) *
			// rotation
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Data->shader.SetUniform("transform", transform);


		s_Data->vertexArray.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		s_Data->vertexArray.Unbind();
	}

	void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& size, Texture2D& texture)
	{
		s_Data->shader.Bind();
		texture.Bind();

		glm::mat4 transform = // TRS - transformation rotation scale
			glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f }) *
			// rotation
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Data->shader.SetUniform("transform", transform);

		s_Data->vertexArray.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		s_Data->vertexArray.Unbind();
	}

}