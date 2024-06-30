#include "afpch.h"
#include "Shader.h"

#include <glad/glad.h>

void AF::Shader::Init(const std::string& vertexSource, const std::string& fragmentSource)
{
	const char* vertexSrc = vertexSource.c_str();
	const char* fragmentSrc = fragmentSource.c_str();
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

	m_ShaderProgram = glCreateProgram();
	glAttachShader(m_ShaderProgram, vertexShaderID);
	glAttachShader(m_ShaderProgram, fragmentShaderID);
	glLinkProgram(m_ShaderProgram);

	glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_ShaderProgram, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
	}
	glUseProgram(m_ShaderProgram);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

void AF::Shader::Shutdown()
{
	glDeleteProgram(m_ShaderProgram);
}

void AF::Shader::Bind()
{
	glUseProgram(m_ShaderProgram);
}

void AF::Shader::Unbind()
{
	glUseProgram(0);
}

unsigned int AF::Shader::FindUniformLocation(const std::string& name)
{
	return glGetUniformLocation(m_ShaderProgram, name.c_str());
}

void AF::Shader::SetUniform(const std::string& name, int value)
{
	glUniform1i(FindUniformLocation(name), value);
}

void AF::Shader::SetUniform(const std::string& name, float value)
{
	glUniform1f(FindUniformLocation(name), value);
}

void AF::Shader::SetUniform(const std::string& name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(FindUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void AF::Shader::SetUniform(const std::string& name, const glm::vec2& vec)
{
	glUniform2f(FindUniformLocation(name), vec.x, vec.y);
}

void AF::Shader::SetUniform(const std::string& name, const glm::vec3& vec)
{
	glUniform3f(FindUniformLocation(name), vec.x, vec.y, vec.z);
}

void AF::Shader::SetUniform(const std::string& name, const glm::vec4& vec)
{
	glUniform4f(FindUniformLocation(name), vec.x, vec.y, vec.z, vec.w);
}

