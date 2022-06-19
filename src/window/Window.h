#pragma once

#include <GLFW/glfw3.h>

class Window {
public:
	static int height;
	static int width;
	static GLFWwindow* window;
	static int initialize(int width, int height, const char* title);
	static void terminate();

	static bool isShouldClose();
	static void setShouldClose(bool flag);
	static void swapBuffers();
	static void setCursorMode(int mode);
};

