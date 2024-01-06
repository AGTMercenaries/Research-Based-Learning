#include "input.h"
#include <iostream>

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	::width = width, ::height = height;
}

float lastX = -1, lastY = -1;
float yaw = 90.0, pitch = 0.0;
void mouseMoveCallBack(GLFWwindow* window, double xpos, double ypos) {

	float xPos = static_cast<float>(xpos);
	float yPos = static_cast<float>(ypos);
	float xoffset = xPos - lastX;
	float yoffset = lastY - yPos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	cam.setRotation(glm::quat(glm::vec3(glm::radians(pitch), glm::radians(-yaw), 0.0f)));
}