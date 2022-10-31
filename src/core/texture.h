#pragma once
#include "GL/glew.h"
#include <stb_image.h>
#include <iostream>

namespace Nata
{
	class Texture
	{
	public:
		static int Load(const char* path);
	};
}