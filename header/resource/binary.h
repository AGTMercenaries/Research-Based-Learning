#pragma once
#include "resource/location.h"
#include <fstream>
#include <memory>

struct Binary {
	std::fstream stream;

	Binary(Path loc);
	std::unique_ptr<unsigned char[]> getData(size_t pos, size_t len);
};