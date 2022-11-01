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
		Model(std::string fileName, std::string directory, bool gamma = false);

		void Draw(Shader& shader);

	public:
		std::vector<Texture> textures_loaded;
		std::vector<Mesh> meshes;
		const char* directory;
		bool gammaCorrection;

	private:
		std::string path;
		void Init
		(std::string fileName, std::string directory);
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	};

}