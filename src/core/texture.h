#pragma once
#include "GL/glew.h"
#include <stb_image.h>
#include <iostream>
#include <string>

namespace Nata
{
	class Texture
	{
	public:
		unsigned int id;
		// diffuse or specular
		std::string type;
		std::string path;
		
		static int Load(std::string path);
	};
}