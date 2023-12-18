#pragma once
#include "gl.h"
#include "glm.h"
#include "render/shader/checker.h"
#include <string_view>

struct Shader {
private:
	unsigned int ID;

public:
	Shader() = default;
	Shader(std::string name);

	void use();
	void setUniformMatrix4fv(const char* name, glm::mat4x4 val);
};