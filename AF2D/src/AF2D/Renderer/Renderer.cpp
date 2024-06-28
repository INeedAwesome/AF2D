#include "afpch.h"
#include "Renderer.h"

#include <string>

#include "AF2D/Renderer/Shader.h"

#include <glad/glad.h>

namespace AF {

	struct RendererData {
		GLuint VertexArray;
		GLuint VertexBuffer;
		GLuint ElementBuffer;

		Shader shader;

		unsigned int Width;
		unsigned int Height;
		int Scale;

	};

	static float verticesData[] = {
		-0.0f, -0.0f, 0.0f,		0.0f, 0.0f,
		 1.0f, -0.0f, 0.0f,		1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,		1.0f, 1.0f,
		-0.0f,  1.0f, 0.0f,		0.0f, 1.0f
	};


	static unsigned int elements[] = {
		0, 1, 2, 0, 2, 3
	};

	static RendererData* s_Data;

	void Renderer::Init()
	{
		s_Data = new RendererData();

		glGenVertexArrays(1, &s_Data->VertexArray);
		glBindVertexArray(s_Data->VertexArray);

		glGenBuffers(1, &s_Data->VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, s_Data->VertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, _countof(verticesData) * sizeof(float), verticesData, GL_STATIC_DRAW);

		glGenBuffers(1, &s_Data->ElementBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_Data->ElementBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _countof(elements)*sizeof(unsigned int), elements, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(sizeof(float)*3));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);

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

void main()
{
	FragColor = vec4(oTexCoords.x, oTexCoords.y, 0.0f, 1.0f);
} 
)""";
		s_Data->shader.Init(vertexShaderSource, fragmentShaderSource);

	}

	void Renderer::Shutdown()
	{
	}

	void Renderer::Begin()
	{
		glEnable(GL_DEPTH_TEST);
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
	}

	void Renderer::SetScale(int scale)
	{
		s_Data->Scale = scale;
	}

	void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& size)
	{
		s_Data->shader.Bind();

		glm::mat4 view = glm::ortho(0.0f, ((float)s_Data->Width/ (float)s_Data->Height)* (float)s_Data->Scale, 0.0f, (float)s_Data->Scale, -100.0f, 100.0f);
		s_Data->shader.SetUniform("view", view);

		glm::mat4 transform = // TRS - transformation rotation scale
			glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f }) *
			// rotation
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Data->shader.SetUniform("transform", transform);


		glBindVertexArray(s_Data->VertexArray);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

}