#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include "stbimage/stb_image.h"
#include <string>

struct Texture {
private:
	unsigned int ID;

public:
	Texture() = default;
	Texture(std::string name);

	void use();
};