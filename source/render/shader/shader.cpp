#include "render/shader/shader.h"
#include "utils/file.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <cassert>

Shader::Shader(std::string name) {

	std::string vs = getFile("shader\\" + name + ".vs");
	std::string fs = getFile("shader\\" + name + ".fs");
	const char* vShaderCode = vs.c_str();
	const char* fShaderCode = fs.c_str();

	unsigned int vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkShaderCompile(vertex, name + ".vs");

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkShaderCompile(fragment, name + ".fs");

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkProgramLink(ID, name);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}
void Shader::use() {
	glUseProgram(ID);
}

void Shader::setUniformMatrix4fv(const char* name, glm::mat4x4 val) {
	int loc = glGetUniformLocation(ID, name);
	if (loc == -1) {
		std::cout << "UNIFORM ERROR : " << name << " not found." << std::endl;
		assert(false);
	}
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(val));
}