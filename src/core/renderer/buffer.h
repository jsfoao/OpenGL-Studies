#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <vector>

using namespace std;

namespace Nata
{
	struct VAOAttrib
	{
		VAOAttrib(unsigned int index, unsigned int count)
		{
			this->index = index;
			this->count = count;
		}

		unsigned int index;
		unsigned int count;
	};

	class Buffer
	{
	public:
		Buffer(){ ID = 0; };

		~Buffer(){};
		
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		unsigned int GetID() const { return ID; };

	protected:
		unsigned int ID;
	};

	class VBO : Buffer
	{
	public:
		VBO(const vector<float> data, unsigned int componentCount);

		void Bind() const;
		void Unbind() const;
		unsigned int GetID() const { return ID; };

		unsigned int componentCount;
	};

	class EBO : Buffer
	{
	public:
		EBO(const vector<int> data, const unsigned int size);

		void Bind() const;
		void Unbind() const;
	};
	
	class VAO
	{
	public:
		unsigned int ID;

		VAO();
		~VAO();

		void Bind() const;
		void Unbind() const;

		void AddVBOAttrib(const VBO& vbo, const unsigned int count);

	protected:
		vector<VBO> m_VBOs;
		unsigned int m_Index;
		unsigned int m_Offset;
	};
}