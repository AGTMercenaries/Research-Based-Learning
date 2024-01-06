#include "render/camera.h"
#include "misc.h"

Camera::Camera() :
	pos(glm::vec3(0.0f, 0.0f, 3.0f)),
	front(glm::vec3(0.0f, 0.0f, -1.0f)),
	up(glm::vec3(0.0f, 1.0f, 0.0f)),
	right(glm::cross(up, front)),
	rot(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)),
	fov(glm::radians(45.0f)),
	zNear(0.1f),
	zFar(100.0f)
{}

glm::mat4x4 Camera::getMatrix() {

	glm::mat4 view = glm::lookAt(pos, pos + rot * front, rot * up);

	glm::mat4 proj(1.0);
	proj = glm::perspective(fov, (float)width / (float)height, zNear, zFar);

	return proj * view;
}

void Camera::setRotation(glm::quat v) {
	rot = v;
}

