#include "afpch.h"
#include "VertexArray.h"

#include <glad/glad.h>

namespace AF {

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_VertexArrayObject);
	}

	void VertexArray::Init(float* verticesData, int vertArraySize, unsigned int* indicesData, int indicesArraySize)
	{
		glGenVertexArrays(1, &m_VertexArrayObject);
		glBindVertexArray(m_VertexArrayObject);

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertArraySize * sizeof(float), verticesData, GL_STATIC_DRAW);

		glGenBuffers(1, &m_ElementBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesArraySize * sizeof(unsigned int), indicesData, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(sizeof(float) * 3));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(m_VertexArrayObject);
	}

	void VertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

}
