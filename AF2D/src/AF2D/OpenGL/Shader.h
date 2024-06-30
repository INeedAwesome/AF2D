#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

namespace AF {

	class Shader
	{
	public:
		void Init(const std::string& vertexSource, const std::string& fragmentSource);
		void Shutdown();

		void Bind();
		void Unbind();

		unsigned int FindUniformLocation(const std::string& name);

		void SetUniform(const std::string& name, int value);
		void SetUniform(const std::string& name, const glm::mat4& matrix);

	private:
		unsigned int m_ShaderProgram;

	};

}

