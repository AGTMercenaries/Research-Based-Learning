#pragma once
#include "resource/location.h"
#include <fstream>

struct Binary {
private:
	std::fstream stream;

public:
	Binary(Path loc);
	unsigned char* getData(size_t pos, size_t len);
};