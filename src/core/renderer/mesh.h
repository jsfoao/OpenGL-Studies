#pragma once
#include "core/glm_math.h"
#include <vector>
#include "texture.h"
#include "shader.h"

using namespace std;

namespace Nata
{
	struct Vertex
	{
		vec3 Position;
		vec3 Normal;
		vec2 TexCoords;
	};

	class Mesh
	{
	public:
		//mesh data
		vector<Vertex> vertices;
		vector<unsigned int> indices;

		Mesh(vector<Vertex>& vertices, vector<unsigned int>& indices);
		Mesh(vector<Vertex>& vertices);
		Mesh(vector<float>& data);

		void Draw();

	private:
		unsigned int VAO, VBO, EBO;
		bool useIndices;
		void SetupMesh();

	public:
		static vector<Vertex> ToVertexVector(vector<float>& data);
	};
}