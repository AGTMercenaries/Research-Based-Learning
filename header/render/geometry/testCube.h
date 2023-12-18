#pragma once
#include "gl.h"
#include "render/shader/shader.h"
#include "render/camera.h"
#include "misc.h"

struct TestCube {
private:
	unsigned int VAO;
	Shader shader;

public:
	TestCube(GLFWwindow *window);
	void render();
};