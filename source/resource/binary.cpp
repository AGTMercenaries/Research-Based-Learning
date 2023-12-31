#include "resource/binary.h"

#include <fstream>
#include <iostream>
#include <cassert>

Binary::Binary(Path loc) : data(nullptr) {
	std::ifstream ifs(loc.path, std::ios::in | std::ios::binary);
	if (!ifs.is_open()) {
		std::cout << "RESOURCE::ERROR::failed to open binary file : " << loc.path << std::endl;
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
