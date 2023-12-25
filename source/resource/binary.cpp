#include "resource/binary.h"

#include <fstream>
#include <iostream>
#include <cassert>

Binary::Binary(Location loc, Extension ext) : data(nullptr) {
	std::ifstream ifs(getPath(loc, ext), std::ios::in | std::ios::binary);
	if (!ifs.is_open()) {
		std::cout << "RESOURCE::ERROR::failed to open binary file : " << loc << ext << std::endl;
		assert(false);
	}
	ifs.seekg(0, ifs.end);
	size_t fileSize = ifs.tellg();
	ifs.seekg(ifs.beg);

	data = new unsigned char[fileSize];
	ifs.read((char*)data, fileSize);
	ifs.close();
}
Binary::~Binary() {
	delete data;
}
