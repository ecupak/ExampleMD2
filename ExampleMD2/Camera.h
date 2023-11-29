#pragma once

#include <glm/glm/glm.hpp>
#include "KeyboardManager.h"


class Camera
{
public:
	Camera() = default;

	void Update(const float deltaTime, const KeyboardManager& km);
	void HandleInput(const float deltaTime, const KeyboardManager& km);

	void MoveForward(const float deltaTime, const bool moveOnYAxis);
	void MoveBackward(const float deltaTime, const bool moveOnYAxis);

	void MoveLeft(const float deltaTime);
	void MoveRight(const float deltaTime);

	void HandleMouse(const float x, const float y);

	glm::mat4 GetViewMatrix();

	glm::vec3 position_{ 0.0f, 0.0f, 40.0f };
	glm::vec3 front_{ 0.0f, 0.0f, -1.0f };
	glm::vec3 up_{ 0.0f, 1.0f, 0.0f };
	glm::vec3 right_{ 1.0f, 0.0f, 0.0f };
	glm::vec3 worldUp_{ 0.0f, 1.0f, 0.0f };

	float speed_{ 10.0f };

	float yaw_{ -90.0f };
	float pitch_{ 0.0f };

	float fov_{ 45.0f };

	float xPrev{ 0.0f };
	float yPrev{ 0.0f };

	float sensitivity_{ 0.3f };

	bool isFirstInput_{ true };
};

