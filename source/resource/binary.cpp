#include "resource/binary.h"

#include <fstream>
#include <iostream>
#include <cassert>

Binary::Binary(Path loc) {
	stream.open(loc.path, std::ios::in | std::ios::binary);
	//if (!stream.is_open()) {
	//	std::cout << "RESOURCE::ERROR::failed to open binary file : " << loc.path << std::endl;
	//	assert(false);
	//}
}
std::unique_ptr<unsigned char[]> Binary::getData(size_t pos, size_t len) {
	stream.seekg(pos);
	unsigned char* res = new unsigned char[len];
	stream.read((char*)res, len);
	return std::unique_ptr<unsigned char[]>(res);
}
