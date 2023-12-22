#include "render/texture/image.h"
#include "render/texture/texture.h"
#include "utils/file.h"
#include "gl.h"

#include <string>
#include <iostream>
#include <cassert>

Texture::Texture(std::string location) : ID(0) {
	int width, height, nrChannels;
	
	std::string path = getFullPath(location);
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (!data) {
		std::cout << "Failed to load texture" << std::endl;
		assert(false);
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

void Texture::use() {
	glBindTexture(GL_TEXTURE_2D, ID);
}