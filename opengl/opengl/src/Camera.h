#pragma once

#include <glm/glm.hpp>

class Camera
{
	glm::vec3 position;
	glm::vec3 viewDirection; // Needs to be normalized (a unit vector)
	const glm::vec3 UP;
	glm::vec2 oldMousePosition;
	glm::vec3 strafeDirection;

	static const float MOVEMENT_SPEED;

public:
	Camera();
	virtual ~Camera();

	void mouseUpdate(const glm::vec2 &newMousePosition);
	glm::mat4 getWorldToViewMatrix() const;
    glm::vec3 getPosition();

	void moveForward();
	void moveBackward();
	void strafeLeft();
	void strafeRight();
	void moveUp();
	void moveDown();
};

