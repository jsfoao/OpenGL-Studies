#include "mesh.h"

namespace Nata
{
	Mesh::Mesh(vector<Vertex>& vertices, vector<unsigned int>& indices, unsigned int drawType)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->drawType = drawType;
		useIndices = true;

		SetupMesh();
	}

	Mesh::Mesh(vector<Vertex>& vertices, unsigned int drawType)
	{
		this->vertices = vertices;
		this->drawType = drawType;
		useIndices = false;
		
		SetupMesh();
	}

	Mesh::Mesh(vector<float>& data, unsigned int drawType)
	{
		this->vertices = ToVertexVector(data);
		this->drawType = drawType;
		useIndices = false;

		SetupMesh();
	}

	void Mesh::Draw()
	{
		// draw mesh
		glBindVertexArray(VAO);
		if (drawType == N_DRAW_ELEMENTS)
		{
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		}
		else if (drawType == N_DRAW_ARRAYS)
		{
			glDrawArrays(GL_TRIANGLES, 0, vertices.size());
		}
		else if (drawType == N_DRAW_LINES)
		{
			glDrawArrays(GL_LINES, 0, vertices.size());
		}
		glBindVertexArray(0);
	}

	void Mesh::SetupMesh()
	{
		// initialize buffer objects
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		// send vertices data
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		if (indices.size() > 0)
		{
			// send indices data
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
		}

		// how to interpret data
		// vertex positions
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glEnableVertexAttribArray(0);
		// vertex normals
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		glEnableVertexAttribArray(1);
		// vertex texture coords
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
		glEnableVertexAttribArray(2);

	}

	vector<Vertex> Mesh::ToVertexVector(vector<float>& data)
	{
		vector<Vertex> output;
		Vertex vertex;
		for (unsigned int i = 0; i < data.size(); i+=8)
		{
			vertex.Position.x = data[i];
			vertex.Position.y = data[i + 1];
			vertex.Position.z = data[i + 2];

			vertex.Normal.x = data[i + 3];
			vertex.Normal.y = data[i + 4];
			vertex.Normal.z = data[i + 5];

			vertex.TexCoords.x = data[i + 6];
			vertex.TexCoords.y = data[i + 7];

			output.push_back(vertex);
		}
		return output;
	}
	Vertex::Vertex()
	{
		this->Position = vec3(0.f);
		this->Normal = vec3(0.f);
		this->TexCoords = vec2(0.f);
	}

	Vertex::Vertex(vec3 position)
	{
		this->Position = position;
		this->Normal = vec3(0.f);
		this->TexCoords = vec2(0.f);
	}

	Vertex::Vertex(vec3 position, vec3 normal, vec2 texCoords)
	{
		this->Position = position;
		this->Normal = normal;
		this->TexCoords = TexCoords;
	}

	Vertex::Vertex(float posX, float posY, float posZ, float normX, float normY, float normZ, float texCoordX, float texCoordY)
	{
		this->Position = vec3(posX, posY, posZ);
		this->Normal = vec3(normX, normY, normZ);
		this->TexCoords = vec2(texCoordX, texCoordY);
	}

}