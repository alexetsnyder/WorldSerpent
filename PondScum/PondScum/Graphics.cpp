#include "Graphics.h"
#include <iostream>

float TriangleVertices[] = {
  -0.5f, -0.5f, 0.0f,
   0.5f, -0.5f, 0.0f,
   0.0f,  0.5f, 0.0f
};

float SquareVertices[] = {
  -0.5f,  0.5f, 0.0f,
   0.5f,  0.5f, 0.0f,
  -0.5f, -0.5f, 0.0f,

  -0.5f, -0.5f, 0.0f,
   0.5f,  0.5f, 0.0f,
   0.5f, -0.5f, 0.0f,
};

Triangle::Triangle()
{
	VAO = 0;
	VBO = 0;
}

void Triangle::init()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(TriangleVertices), TriangleVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Triangle::draw()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}

Square::Square()
{
	VAO = 0;
	VBO = 0;
}

void Square::init()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(SquareVertices), SquareVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Square::draw()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

Circle::Circle()
{
	VAO = 0;
	VBO = 0;
}

void Circle::init()
{

}

void Circle::draw()
{

}

bool Graphics::init(GLADloadproc procAddress)
{
	bool success = gladLoadGLLoader(procAddress);

	if (success)
	{
		shader.setVShader("..\\Shaders\\vShader.glsl");
		shader.setFShader("..\\Shaders\\fShader.glsl");

		char infoLog[512];

		if (!shader.compile(infoLog))
		{
			cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << endl;
			success = false;
		}

		if (success && !shader.link(infoLog))
		{
			cout << "ERROR::SHADER::LINK_FAILED\n" << infoLog << endl;
			success = false;
		}
	}

	if (success)
	{
		projection = glm::mat4(1.0f);
		view = glm::mat4(1.0f);

		triangle.init();
		square.init();
		circle.init();
	}

	return success;
}

void Graphics::setProjection(glm::mat4 projection)
{
	shader.use();
	this->projection = projection;
	shader.setUniformMatrix4fv("projection", projection);
}

void Graphics::setView(glm::mat4 view)
{
	shader.use();
	this->view = view;
	shader.setUniformMatrix4fv("view", view);
}

void Graphics::draw(Shape shape, glm::mat4 model)
{
	shader.use();
	
	shader.setUniformMatrix4fv("model", model);
	
	if (shape == Shape::TRIANGLE)
	{
		triangle.draw();
	}
	else if (shape == Shape::SQUARE)
	{
		square.draw();
	}
	else //(shape == Shape::CIRCLE)
	{
		circle.draw();
	}
}