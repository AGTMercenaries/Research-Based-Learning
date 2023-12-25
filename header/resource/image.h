#pragma once

#include "resource/location.h"

struct Image {
	int width, height, nrChannels;
	unsigned char* data;
	Image(Location loc);
	~Image();
};