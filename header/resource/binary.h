#pragma once
#include "resource/location.h"

struct Binary {
	unsigned char* data;

	Binary(Path loc);
	~Binary();
};