#pragma once
#include <vector>

#include <glm/glm.hpp>

class Grid
{
	public:
		Grid();
		glm::vec3 GetRandomColor();

	private:
		int rows, cols;

		std::vector<std::vector<int>> grid;
};

