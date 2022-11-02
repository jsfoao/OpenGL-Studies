#include "mesh.h"

namespace Nata
{
	Mesh::Mesh(vector<Vertex>& vertices, vector<unsigned int>& indices)
	{
		this->vertices = vertices;
		this->indices = indices;
		useIndices = true;

		SetupMesh();
	}

	Mesh::Mesh(vector<Vertex>& vertices)
	{
		this->vertices = vertices;
		useIndices = false;

		SetupMesh();
	}

	Mesh::Mesh(vector<float>& data)
	{
		this->vertices = ToVertexVector(data);
		useIndices = false;

		SetupMesh();
	}

	void Mesh::Draw()
	{
		// draw mesh
		glBindVertexArray(VAO);
		if (useIndices)
		{
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);
	}

	void Mesh::SetupMesh()
	{
		/*
		Note on structs
		Structs have a great property in C++ that their memory layout is sequential.

		Vertex vertex;
		vertex.Position = glm::vec3(0.2f, 0.4f, 0.6f);
		vertex.Normal = glm::vec3(0.0f, 1.0f, 0.0f);
		vertex.TexCoords = glm::vec2(1.0f, 0.0f);
		// = [0.2f, 0.4f, 0.6f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f];
		*/

		// initialize buffer objects
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		// send vertices data
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		if (useIndices)
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
}