#include "resource/text.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <cassert>

Text::Text(Path loc) {
	std::ifstream stream;
	stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		stream.open(loc.path);
		std::stringstream ss;
		ss << stream.rdbuf();
		stream.close();
		context = ss.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "RESOURCE::ERROR::failed to read Text : " << loc.path << std::endl;
		assert(false);
	}
}