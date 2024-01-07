#include "render/shader/shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <cassert>
#include <resource.h>

Shader::Shader(Location loc) {
	auto vShader = Text(VertexShader(loc)), fShader = Text(FragmentShader(loc));
	const char* vShaderCode = vShader.context.c_str();
	const char* fShaderCode = fShader.context.c_str();

	unsigned int vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkShaderCompile(vertex, loc);

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkShaderCompile(fragment, loc);

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkProgramLink(ID, loc);

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