#pragma once
#include "core/glm_math.h"
#include <vector>
#include "texture.h"
#include "shader.h"

#define N_DRAW_ELEMENTS 0
#define N_DRAW_ARRAYS 1
#define N_DRAW_LINES 2

using namespace std;

namespace Nata
{
	struct Vertex
	{
		vec3 Position;
		vec3 Normal;
		vec2 TexCoords;

		Vertex();
		Vertex(vec3 position);
		Vertex(vec3 position, vec3 normal, vec2 texCoords);
		Vertex(float posX, float posY, float posZ, float normX = 0.f, float normY = 0.f, float normZ = 0.f, float texCoordX = 0.f, float texCoordY = 0.f);
	};

	class Mesh
	{
	public:
		//mesh data
		vector<Vertex> vertices;
		vector<unsigned int> indices;

		Mesh(vector<Vertex>& vertices, vector<unsigned int>& indices, unsigned int drawType = N_DRAW_ELEMENTS);
		Mesh(vector<Vertex>& vertices, unsigned int drawType = N_DRAW_ELEMENTS);
		Mesh(vector<float>& data, unsigned int drawType = N_DRAW_ELEMENTS);

		void Draw();

	private:
		unsigned int VAO, VBO, EBO;
		void SetupMesh();
		bool useIndices;
		unsigned int drawType;


	public:
		static vector<Vertex> ToVertexVector(vector<float>& data);
	};
}