#include "Camera.h"

#include <glm/glm/gtc/matrix_transform.hpp>

#include <iostream>


void Camera::Update(const float deltaTime, const KeyboardManager& km)
{
	HandleInput(deltaTime, km);

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
	direction.y = sin(glm::radians(pitch_));
	direction.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
	front_ = glm::normalize(direction);

	right_ = glm::normalize(glm::cross(front_, worldUp_));
	up_ = glm::normalize(glm::cross(right_, front_));
}


void Camera::HandleInput(const float deltaTime, const KeyboardManager& km)
{
	// KEYBOARD INPUT //

	bool isRotationMode{ km.IsPressed(Action::ToggleRotationMode) };

	// Can't switch to this mode if in rotation mode.
	bool isAxisSwitched{ isRotationMode ? false : km.IsPressed(Action::TogglePrimaryAxis) };

	if (km.IsPressed(Action::Up))
	{
		if (isRotationMode)
		{
			pitch_ += 1.0f;
		}
		else
		{
			MoveForward(deltaTime, isAxisSwitched);
		}
	}
	else if (km.IsPressed(Action::Down))
	{
		if (isRotationMode)
		{
			pitch_ -= 1.0f;
		}
		else
		{
			MoveBackward(deltaTime, isAxisSwitched);
		}
	}

	if (km.IsPressed(Action::Left))
	{
		if (isRotationMode)
		{
			yaw_ -= 1.0f;
		}
		else
		{
			MoveLeft(deltaTime);
		}
	}
	else if (km.IsPressed(Action::Right))
	{
		if (isRotationMode)
		{
			yaw_ += 1.0f;
		}
		else
		{
			MoveRight(deltaTime);
		}
	}

	//// MOUSE INPUT //

	//float2 mousePosition{ km.GetMousePosition() };

	//if (isFirstInput_)
	//{
	//	if (mousePosition.x_ != 0.0f || mousePosition.y_ != 0.0f)
	//	{
	//		xPrev = mousePosition.x_;
	//		yPrev = mousePosition.y_;
	//		isFirstInput_ = false;
	//	}
	//}

	//float xOffset{ mousePosition.x_ - xPrev };
	//float yOffset{ yPrev - mousePosition.y_ };

	//xPrev = mousePosition.x_;
	//yPrev = mousePosition.y_;

	//xOffset *= sensitivity_;
	//yOffset *= sensitivity_;

	//yaw_ += xOffset;
	//pitch_ += yOffset;

	if (pitch_ > 89.0f)
	{
		pitch_ = 89.0f;
	}
	else if (pitch_ < -89.0f)
	{
		pitch_ = -89.0f;
	}
}


void Camera::MoveForward(const float deltaTime, const bool moveOnYAxis)
{
	position_ += speed_ * deltaTime * (moveOnYAxis ? up_ : front_);
}


void Camera::MoveBackward(const float deltaTime, const bool moveOnYAxis)
{
	position_ -= speed_ * deltaTime * (moveOnYAxis ? up_ : front_);
}


void Camera::MoveLeft(const float deltaTime)
{
	position_ -= right_ * deltaTime * speed_;
}


void Camera::MoveRight(const float deltaTime)
{
	position_ += right_ * deltaTime * speed_;
}


void Camera::HandleMouse(const float x, const float y)
{
	if (isFirstInput_)
	{
		if (x != 0.0f || y != 0.0f)
		{
			xPrev = x;
			yPrev = y;
			isFirstInput_ = false;
		}
	}

	float xOffset{ x - xPrev };
	float yOffset{ yPrev - y };

	xPrev = x;
	yPrev = y;

	xOffset *= sensitivity_;
	yOffset *= sensitivity_;

	yaw_ += xOffset;
	pitch_ += yOffset;

	if (pitch_ > 89.0f)
	{
		pitch_ = 89.0f;
	}
	else if (pitch_ < -89.0f)
	{
		pitch_ = -89.0f;
	}
}


glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(position_, position_ + front_, up_);	
}