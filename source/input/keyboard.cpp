#include "input.h"
#include "game.h"

void processKeyboard(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	float cameraSpeed = 0.02f;
	glm::vec3 front = glm::normalize(glm::vec3(game.cam.front.x, 0.0f, game.cam.front.z));
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 left = glm::cross(up, front);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		game.cam.pos += cameraSpeed * front;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		game.cam.pos -= cameraSpeed * front;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		game.cam.pos += cameraSpeed * left;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		game.cam.pos -= cameraSpeed * left;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		game.cam.pos += cameraSpeed * up;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		game.cam.pos -= cameraSpeed * up;
}