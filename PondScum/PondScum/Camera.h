#pragma once
#include <glm/glm.hpp>

class Camera
{
	public:
		Camera();

		glm::mat4 getViewMatrix();

		void moveLeft(float deltaTime);
		void moveRight(float deltaTime);
		void moveUp(float deltaTime);
		void moveDown(float deltaTime);

	private:
		float cameraSpeedMod;
		glm::vec3 cameraPos;
		glm::vec3 cameraFront;
		glm::vec3 cameraUp;
};

