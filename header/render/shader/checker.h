#pragma once
#include "gl.h"
#include <string>

void checkShaderCompile(unsigned int id, std::string detail);
void checkProgramLink(unsigned int id, std::string detail);