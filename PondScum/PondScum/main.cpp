#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Graphics.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"

using namespace std;

void frambuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(Window& window, float deltaTime);

Shader shader;
Camera camera;
unsigned int VAO, VBO;

int main(int argc, char** argv)
{
	Window window;
	shared_ptr<Graphics> graphics = Graphics::instance();

	if (!window.init())
	{
		cout << "Failed to initiazlize GLFW window.\n";
		window.free();
		return -1;
	}

	if (!graphics->init((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize Graphics class.\n";
		window.free();
		return -1;
	}

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	window.setFrambufferCallback(frambuffer_size_callback);

	glm::vec2 trianglePositions[] =
	{
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(-1.0f, 0.0f),
		glm::vec2(0.0f, -1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(-1.0f, -1.0f),
		glm::vec2(0.0f, 0.0f),
	};

	graphics->setProjection(glm::ortho(-6.0f, 6.0f, -6.0f, 6.0f, 0.1f, 6.0f));

	while (window.isRunning())
	{
		float deltaTime = window.frameTick();

		processInput(window, deltaTime);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		graphics->setView(camera.getViewMatrix());

		/*for (unsigned int i = 0; i < 7; ++i)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(trianglePositions[i], 0.0f));
			graphics->draw(Shape::TRIANGLE, model);
		}*/
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		graphics->draw(Shape::HEXAGON, model);

		window.swapBuffers();
		window.pollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	shader.free();
	window.free();

	return 0;
}

void frambuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(Window& window, float deltaTime)
{
	if (window.isKeyPressed(GLFW_KEY_ESCAPE))
	{
		window.close();
	}
	if (window.isKeyPressed(GLFW_KEY_W))
	{
		camera.moveUp(deltaTime);
	}
	if (window.isKeyPressed(GLFW_KEY_S))
	{
		camera.moveDown(deltaTime);
	}
	if (window.isKeyPressed(GLFW_KEY_A))
	{
		camera.moveLeft(deltaTime);
	}
	if (window.isKeyPressed(GLFW_KEY_D))
	{
		camera.moveRight(deltaTime);
	}
}
