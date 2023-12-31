#define STB_IMAGE_IMPLEMENTATION
#include <stbimage/stb_image.h>
#include <cassert>
#include "resource/image.h"
#include <iostream>

Image::Image(Path loc) {
	data = stbi_load(loc.path.c_str(), &width, &height, &nrChannels, 0);

	if (!data) {
		std::cout << "RESOURCE::IMAGE::failed to load the image : " << loc.path << std::endl;
		assert(false);
	}
}
Image::~Image() {
	stbi_image_free(data);
}