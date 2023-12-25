#pragma once
#include "resource/location.h"

struct Binary {
	unsigned char* data;

	Binary(Location loc, Extension ext);
	~Binary();
};