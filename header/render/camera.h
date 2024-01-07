#pragma once
#include "gl.h"
#include "utils/glm.h"
#include <iostream>

struct Camera {
	glm::vec3 pos;

	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;

	float fov, zNear, zFar;

	Camera();
	glm::mat4x4 getMatrix();
	void setFront(glm::vec3 v);
};
