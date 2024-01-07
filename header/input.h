#pragma once
#include "gl.h"
#include "utils/glm.h"

void processInput(GLFWwindow* window);
void processKeyboard(GLFWwindow* window);

void setInputCallbacks(GLFWwindow* window);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void mouseMoveCallBack(GLFWwindow* window, double xpos, double ypos);