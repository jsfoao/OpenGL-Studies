#include "model.h"

namespace Nata
{
	Model::Model(string path)
	{
		Load(path);
	}

	void Model::Draw()
	{
		for (unsigned int i = 0; i < meshes.size(); i++)
		{
			meshes[i].Draw();
		}
	}

	void Model::Load(string path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		}

		this->ProcessNode(scene->mRootNode, scene);
	}

	void Model::ProcessNode(aiNode* node, const aiScene* scene)
	{
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			this->meshes.push_back(this->ProcessMesh(mesh, scene));
		}

		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			this->ProcessNode(node->mChildren[i], scene);
		}
	}

	Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

		// process vertices
		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			vec3 vert;
			vert.x = mesh->mVertices[i].x;
			vert.y = mesh->mVertices[i].y;
			vert.z = mesh->mVertices[i].z;
			vertex.Position = vert;

			vert.x = mesh->mNormals[i].x;
			vert.y = mesh->mNormals[i].y;
			vert.z = mesh->mNormals[i].z;
			vertex.Normal = vert;

			if (mesh->mTextureCoords[0])
			{
				vert.x = mesh->mTextureCoords[0][i].x;
				vert.y = mesh->mTextureCoords[0][i].y;
				vertex.TexCoords = vert;
			}
			else
			{
				vertex.TexCoords = vec2(0.f, 0.f);
			}
		}

		// process indices
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		return Mesh(vertices, indices);
	}
}