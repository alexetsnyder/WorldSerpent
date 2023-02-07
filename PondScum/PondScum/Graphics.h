#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <memory>
#include "Shader.h"

class Triangle
{
	public:
		Triangle();

		void init();
		void draw();
		
	private:
		unsigned int VAO, VBO;
};

class Square
{
	public:
		Square();

		void init();
		void draw();

	private:
		unsigned int VAO, VBO;
};

class Circle
{
	public:
		Circle();

		void init();
		void draw();

	private:
		unsigned int VAO, VBO;
};

class Hexagon
{
	public:
		Hexagon();

		void init();
		void draw();

	private:
		unsigned int VAO, VBO;
};

enum Shape
{
	TRIANGLE,
	SQUARE,
	CIRCLE,
	HEXAGON,
};

class Graphics
{
	public:
		Graphics(Graphics const&) = delete;
		Graphics& operator=(Graphics const&) = delete;

		static std::shared_ptr<Graphics> instance()
		{
			static std::shared_ptr<Graphics> g{ new Graphics };
			return g;
		}

		bool init(GLADloadproc procAddress);

		void setProjection(glm::mat4 projection);
		void setView(glm::mat4 view);

		void draw(Shape shape, glm::mat4 model);

	private:
		Graphics() {}

		Shader shader;

		glm::mat4 projection;
		glm::mat4 view;

		Triangle triangle;
		Square square;
		Circle circle;
		Hexagon hex;
};

