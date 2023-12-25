#include "resource/text.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <cassert>

Text::Text(Location loc, Extension ext) {
	std::ifstream stream;
	stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		stream.open(getPath(loc, ext));
		std::stringstream ss;
		ss << stream.rdbuf();
		stream.close();
		context = ss.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "RESOURCE::ERROR::failed to read Text : " << getPath(loc, ext) << std::endl;
		assert(false);
	}
}