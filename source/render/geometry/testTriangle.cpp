#include "render/geometry/testTriangle.h"

Shader shader;
unsigned int VAO;
void initTriangle(GLFWwindow* window) {
	float vertices[] = {
		-0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f,   // 右上角
		0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f,  // 右下角
		0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, // 左下角
	};

	// 设置 VBO，并 绑定至 VAO
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	shader = Shader("testTriangle");
}
void testTriangle(GLFWwindow* window, Camera camera) {
	shader.setUniformMatrix4fv("mvp", camera.getMatrix());
	shader.use();
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}