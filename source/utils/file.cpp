#include "utils/file.h"

std::string getFile(std::string name) {
	std::ifstream stream;
	std::string str;
	stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		stream.open(path + std::string("resource\\") + name);
		std::stringstream ss;
		ss << stream.rdbuf();
		stream.close();
		str = ss.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::FAILED TO READ SHADER : " << e.what() << std::endl;
		assert(false);
	}
	return std::move(str);
}