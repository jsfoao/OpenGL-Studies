#pragma once
#include "core/glm_math.h"
#include <vector>
#include "texture.h"
#include "shader.h"
#include "mesh.h"

#include "assimp/config.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;
namespace Nata
{
	class Model
	{
	public:
		Model(string path);
		void Draw();

	public:
		vector<Mesh> meshes;
		string directory;
		bool gammaCorrection;

	private:
		void Load(string path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	};
}
