#include "render/shader/checker.h"

#include <iostream>
#include <cassert>

void checkShaderCompile(unsigned int id, std::string detail) {
	static int success;
	static char infoLog[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(id, 512, nullptr, infoLog);
		std::cout << "ERROR :: SHADER COMPILE FAILED at " << detail << "(" << id << ") " << ":\n" << infoLog << std::endl;
		assert(false);
	}
}

void checkProgramLink(unsigned int id, std::string detail) {
	static int success;
	static char infoLog[512];
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR :: PROGRAM LINK FAILED at " << detail << ":\n" << infoLog << std::endl;
		assert(false);
	}
}

