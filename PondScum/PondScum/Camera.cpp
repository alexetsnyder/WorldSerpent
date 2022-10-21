#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera()
{
	cameraSpeedMod = 3.5f;
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::moveUp(float deltaTime)
{
	float cameraSpeed = static_cast<float>(cameraSpeedMod * deltaTime);
	cameraPos += cameraSpeed * cameraUp;
}

void Camera::moveDown(float deltaTime)
{
	float cameraSpeed = static_cast<float>(cameraSpeedMod * deltaTime);
	cameraPos -= cameraSpeed * cameraUp;
}

void Camera::moveLeft(float deltaTime)
{
	float cameraSpeed = static_cast<float>(cameraSpeedMod * deltaTime);
	cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void Camera::moveRight(float deltaTime)
{
	float cameraSpeed = static_cast<float>(cameraSpeedMod * deltaTime);
	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}