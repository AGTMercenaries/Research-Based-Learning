#include <iostream>
#include <format>

#include "gl.h"
#include "input.h"
#include "render.h"
#include "misc.h"

int main() {
	// һЩ׼������
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Game", NULL, NULL);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// ���ô��ڴ�С
	setInputCallbacks(window);
	glEnable(GL_DEPTH_TEST);

	//initTriangle(window);
	TestCube cube(window);
	// ������Ⱦѭ��
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glDepthMask(GL_FALSE);
		// ��������һЩ��Ⱦ����
		//testTriangle(window, cam);
		cube.render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// �����ڴ�

	glfwTerminate();
	return 0;
}
