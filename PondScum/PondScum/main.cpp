#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Window.h"
#include "Camera.h"

using namespace std;

void frambuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(Window& window, float deltaTime);
void openGlTriangle();

Shader shader;
Camera camera;
unsigned int VAO, VBO;

int main(int argc, char** argv)
{
	Window window;

	if (!window.init())
	{
		cout << "Failed to initiazlize GLFW window.\n";
		window.free();
		return -1;
	}

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD.\n";
		window.free();
		return -1;
	}

	/*glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	vec = trans * vec;
	cout << vec.x << vec.y << vec.z << endl;*/

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	window.setFrambufferCallback(frambuffer_size_callback);

	openGlTriangle();

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

	shader.use();

	//glm::mat4 projection = glm::ortho(0.0f, 6.0f, 0.0f, 6.0f, 0.1f, 6.0f);
	glm::mat4 projection = glm::ortho(-6.0f, 6.0f, -6.0f, 6.0f, 0.1f, 6.0f);
	shader.setUniformMatrix4fv("projection", projection);


	while (window.isRunning())
	{
		float deltaTime = window.frameTick();

		processInput(window, deltaTime);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();
		/*glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);*/

		shader.setUniformMatrix4fv("view", camera.getViewMatrix());

		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 7; ++i)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(trianglePositions[i], 0.0f));
			shader.setUniformMatrix4fv("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		glBindVertexArray(0);

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

void openGlTriangle()
{
	shader = Shader("..\\Shaders\\vShader.glsl", "..\\Shaders\\fShader.glsl");

	char infoLog[512];

	if (!shader.compile(infoLog))
	{
		cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << endl;
		return;
	}

	if (!shader.link(infoLog))
	{
		cout << "ERROR::SHADER::LINK_FAILED\n" << infoLog << endl;
		return;
	}

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);	
}