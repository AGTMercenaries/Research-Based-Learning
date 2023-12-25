#define STB_IMAGE_IMPLEMENTATION
#include "stbimage/stb_image.h"
#include "resource/image.h"
#include <iostream>

Image::Image(Location loc) {
	auto path = getPath(loc, "png");
	data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

	if (!data) {
		std::cout << "RESOURCE::IMAGE::failed to load the image : " << loc << std::endl;
		assert(false);
	}
}
Image::~Image() {
	stbi_image_free(data);
}