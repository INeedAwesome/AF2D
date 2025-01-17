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


		void SetUniform(const std::string& name, int value);
		void SetUniform(const std::string& name, float value);
		void SetUniform(const std::string& name, const glm::mat4& matrix);
		void SetUniform(const std::string& name, const glm::vec2& vec);
		void SetUniform(const std::string& name, const glm::vec3& vec);
		void SetUniform(const std::string& name, const glm::vec4& vec);

	private:
		unsigned int GetUniformLocation(const std::string& name);

	private:
		unsigned int m_ShaderProgram;
		std::unordered_map<std::string, int32_t> m_UniformLocationCache;

	};

}


