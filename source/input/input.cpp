#include "input.h"
#include "game.h"

void processInput(GLFWwindow* window) {
	processKeyboard(window);
}
void setInputCallbacks(GLFWwindow* window) {
	
	// viewport
	glViewport(0, 0, game.width, game.height);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	
	game.lastX = game.width / 2.0f, game.lastY = game.height / 2.0f;
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouseMoveCallBack);
}
