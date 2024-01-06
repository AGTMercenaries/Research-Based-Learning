#pragma once
#include "gl.h"
#include "glm.h"
#include <iostream>

struct Camera {
protected:
	glm::vec3 pos;

	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;

	glm::quat rot;

	float fov, zNear, zFar;

public:
	Camera();
	glm::mat4x4 getMatrix();
	void setRotation(glm::quat v);
	friend void processKeyboard(GLFWwindow* window);
};
