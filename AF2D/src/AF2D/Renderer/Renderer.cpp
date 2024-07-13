#include "afpch.h"
#include "Renderer.h"

#include <string>

#include "AF2D/OpenGL/Shader.h"
#include "AF2D/OpenGL/VertexArray.h"
#include "AF2D/OpenGL/Texture2D.h"

#include <glad/glad.h>

namespace AF {

	struct RendererData {
		VertexArray RenderVertexArray;
		Shader RenderShader;
		Texture2D RendererWhiteTexture;

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

		s_Data->RenderVertexArray.Init(verticesData, _countof(verticesData), elements, _countof(elements));

		std::string vertexShaderSource = R"""(#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 oTexCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 transform;

void main()
{
	gl_Position = projection * view * transform * vec4(aPos, 1.0);
	oTexCoords = aTexCoords;
}
)""";

		std::string fragmentShaderSource = R"""(#version 330 core
out vec4 FragColor;
in vec2 oTexCoords;

uniform sampler2D boundTexture;
uniform vec4 colorTint;


void main()
{
	//FragColor = vec4(oTexCoords.x, oTexCoords.y, 0.0f, 1.0f);
	FragColor = texture(boundTexture, oTexCoords) * colorTint;
	if (FragColor.a < 0.1)
	{
		discard;
	}
} 
)""";
		s_Data->RenderShader.Init(vertexShaderSource, fragmentShaderSource);

		unsigned char* data = new unsigned char[3];
		data[0] = 255; data[1] = 255; data[2] = 255;
		TextureBuffer buffer{data, 1, 1, 3};
		s_Data->RendererWhiteTexture.Init(buffer, Texture2D::LINEAR);

		s_Data->Scale = 1;

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
	}

	void Renderer::Shutdown()
	{
	}

	void Renderer::Begin(Camera& camera)
	{
		glClearColor(0.2f, 0.4f, 1.0f, 1.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		glm::mat4 projection = glm::ortho(0.0f, ((float)s_Data->Width / (float)s_Data->Height) * (float)s_Data->Scale, 0.0f, (float)s_Data->Scale, -100.0f, 100.0f);

		glm::mat4 view = glm::translate(glm::mat4(1), -camera.GetPosition());
		view = glm::rotate(view, glm::radians(camera.GetRotation()), {0, 0, 1});
		view = glm::scale(view, {1, 1, 1});

		s_Data->RenderShader.SetUniform("projection", projection);
		s_Data->RenderShader.SetUniform("view", view);
	}

	void Renderer::End()
	{
	}

	void Renderer::Resize(int newWidth, int newHeight)
	{
		glViewport(0, 0, newWidth, newHeight);
		s_Data->Width = newWidth;
		s_Data->Height= newHeight;
}

	void Renderer::SetScale(int scale)
	{
		s_Data->Scale = scale;
	}

	void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& size)
	{
		DrawQuad(position, size, { 1, 1, 1, 1 });
	}

	void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& colorTint)
	{
		DrawQuad({ position.x, position.y, 0 }, size, colorTint);
	}

	void Renderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& colorTint)
	{
		s_Data->RenderShader.Bind();

		s_Data->RendererWhiteTexture.Bind();

		glm::mat4 transform = // TRS - transformation rotation scale
			glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f }) *
			// rotation
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Data->RenderShader.SetUniform("transform", transform);
		s_Data->RenderShader.SetUniform("colorTint", colorTint);

		s_Data->RenderVertexArray.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		s_Data->RenderVertexArray.Unbind();
	}

	void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& size, Texture2D& texture)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, { 1, 1, 1, 1 });
	}

	void Renderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, Texture2D& texture)
	{
		DrawQuad(position, size, texture, { 1, 1, 1, 1 });
	}

	void Renderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, Texture2D& texture, const glm::vec4& colorTint)
	{
		s_Data->RenderShader.Bind();
		texture.Bind();

		glm::mat4 transform = // TRS - transformation rotation scale
			glm::translate(glm::mat4(1.0f), position) *
			// rotation
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Data->RenderShader.SetUniform("transform", transform);
		s_Data->RenderShader.SetUniform("colorTint", colorTint);

		s_Data->RenderVertexArray.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		s_Data->RenderVertexArray.Unbind();
	}

}