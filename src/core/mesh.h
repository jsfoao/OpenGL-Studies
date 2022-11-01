#pragma once
#include "glm_math.h"
#include <vector>
#include "texture.h"
#include "shader.h"
#include "assimp/config.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

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
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
		void Draw(Shader& shader);

	private:
		unsigned int VAO, VBO, EBO;

		void Init();
	};

	class Model
	{
	public:
		Model(char* path);

		void Draw(Shader& shader);

	private:
		std::vector<Mesh> meshes;
		std::string directory;

		void LoadModel(std::string path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	};

}