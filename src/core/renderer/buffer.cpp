#include "buffer.h"

namespace Nata
{
	VBO::VBO(const vector<float> data, unsigned int componentCount)
	{
		this->componentCount = componentCount;
		glGenBuffers(1, &ID);
		Bind();
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
		Unbind();
	}

	void VBO::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, ID);
	}

	void VBO::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	EBO::EBO(const vector<int> data, const unsigned int size)
	{
		glGenBuffers(1, &ID);
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
		Unbind();
	}

	void EBO::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	}
	void EBO::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	VAO::VAO()
	{
		m_Index = 0;
		m_Offset = 0;
		glGenVertexArrays(1, &ID);
	}

	VAO::~VAO()
	{
		glDeleteVertexArrays(1, &ID);
	}

	void VAO::Bind() const
	{
		glBindVertexArray(ID);
	}

	void VAO::Unbind() const
	{
		glBindVertexArray(0);
	}

	void VAO::AddVBOAttrib(const VBO& vbo, const unsigned int count)
	{
		Bind();
		vbo.Bind();
		glVertexAttribPointer(m_Index, count, GL_FLOAT, GL_FALSE, vbo.componentCount * sizeof(float), (void*)(m_Offset * sizeof(float)));
		glEnableVertexAttribArray(m_Index);
		vbo.Unbind();
		Unbind();
		m_Index++;
		m_Offset += count;
	}
}

