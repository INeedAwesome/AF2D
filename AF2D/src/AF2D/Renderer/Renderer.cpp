#include "afpch.h"
#include "Renderer.h"

#include <string>

#include <glad/glad.h>

namespace AF {

	struct RendererData {
		GLuint VertexArray;
		GLuint VertexBuffer;
		GLuint ElementBuffer;

		GLuint ShaderProgram;
	};

	static float verticesData[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,		1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f,		1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f,		0.0f, 1.0f
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

void main()
{
	gl_Position = vec4(aPos, 1.0);
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

		const char* vertexSrc = vertexShaderSource.c_str();
		const char* fragmentSrc = fragmentShaderSource.c_str();
		unsigned int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		unsigned int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(vertexShaderID, 1, &vertexSrc, 0);
		glShaderSource(fragmentShaderID, 1, &fragmentSrc, 0);
		glCompileShader(vertexShaderID);
		glCompileShader(fragmentShaderID);

		int success = 0;
		char infoLog[512] = { 0 };
		glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
			std::cout << infoLog << std::endl;
		}
		glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
			std::cout << infoLog << std::endl;
		}

		s_Data->ShaderProgram = glCreateProgram();
		glAttachShader(s_Data->ShaderProgram, vertexShaderID);
		glAttachShader(s_Data->ShaderProgram, fragmentShaderID);
		glLinkProgram(s_Data->ShaderProgram);

		glGetProgramiv(s_Data->ShaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(s_Data->ShaderProgram, 512, NULL, infoLog);
			std::cout << infoLog << std::endl;
		}
		glUseProgram(s_Data->ShaderProgram);
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);

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

	void Renderer::DrawQuad()
	{
		glUseProgram(s_Data->ShaderProgram);
		glBindVertexArray(s_Data->VertexArray);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

}