#pragma once
#include <GLFW/glfw3.h>
#include <string>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

class Window
{
	public:
		Window();
		Window(std::string title, int width, int height);

		bool init();

		void setTitle(std::string title);
		void setSize(int width, int height);
		void setWidth(int width);
		void setHeight(int height);
		void setFrambufferCallback(GLFWframebuffersizefun callback);
		bool isKeyPressed(int key);

		float frameTick();
		bool isRunning();
		void close();
		void swapBuffers();
		void pollEvents();
		void free();

	private:
		GLFWwindow* window;
		std::string title;
		int width, height;
		float deltaTime, lastFrame;
};

