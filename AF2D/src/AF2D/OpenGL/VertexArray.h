#pragma once

namespace AF {

	class vertexArray
	{
	public:
		vertexArray() = default;
		~vertexArray();

		void Init(float* verticesData, int vertArraySize, unsigned int* indicesData, int indicesArraySize);
		void Bind();
		void Unbind();


	private:
		unsigned int m_VertexArrayObject;
		unsigned int m_VertexBuffer;
		unsigned int m_ElementBuffer;
	};

}

