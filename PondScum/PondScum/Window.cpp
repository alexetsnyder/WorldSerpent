#include "Window.h"

using namespace std;

Window::Window()
{
	setTitle("");
	setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	deltaTime = 0.0f;
	lastFrame = 0.0f;
}

Window::Window(string title, int width, int height)
{
	setTitle(title);
	setSize(width, height);
}

bool Window::init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (window == NULL)
	{
		return false;
	}
	glfwMakeContextCurrent(window);
	return true;
}

void Window::setTitle(string title)
{
	this->title = title;
}

void Window::setSize(int width, int height)
{
	setWidth(width);
	setHeight(height);
}

void Window::setWidth(int width)
{
	this->width = width;
}

void Window::setHeight(int height)
{
	this->height = height;
}

void Window::close()
{
	glfwSetWindowShouldClose(this->window, true);
}

bool Window::isRunning()
{
	return !glfwWindowShouldClose(window);
}

void Window::swapBuffers()
{
	glfwSwapBuffers(window);
}

void Window::pollEvents()
{
	glfwPollEvents();
}

void Window::free()
{
	glfwTerminate();
}

void Window::setFrambufferCallback(GLFWframebuffersizefun callback)
{
	glfwSetFramebufferSizeCallback(window, callback);
}

bool Window::isKeyPressed(int key)
{
	return glfwGetKey(this->window, key) == GLFW_PRESS;
}

float Window::frameTick()
{
	float currentFrame = static_cast<float>(glfwGetTime());
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	
	return deltaTime;
}