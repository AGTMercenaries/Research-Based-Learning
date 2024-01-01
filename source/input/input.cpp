#include "input.h"

int width = 2400, height = 3600;
Camera cam;

void processInput(GLFWwindow* window) {
	processKeyboard(window);
}
void setInputCallbacks(GLFWwindow* window) {
	
	// viewport
	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	
	lastX = width / 2.0f, lastY = height / 2.0f;
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouseMoveCallBack);
}
