#include <iostream>

#include "input.h"
#include "game.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	game.width = width, game.height = height;
}

float yaw = -90.0, pitch = 0.0;

void mouseMoveCallBack(GLFWwindow* window, double xpos, double ypos) {

	float xPos = static_cast<float>(xpos);
	float yPos = static_cast<float>(ypos);
	float xoffset = xPos - game.lastX;
	float yoffset = game.lastY - yPos;
	game.lastX = static_cast<float>(xpos);
	game.lastY = static_cast<float>(ypos);

	float sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front(1.0);
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	game.cam.setFront(front);

}