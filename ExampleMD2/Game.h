#pragma once

#include <glm/glm/glm.hpp>

#include "md2Model.h"

#include "EGLManager.h"

#include "Camera.h"
#include "KeyboardManager.h"


class Game
{
public:
	Game(const EGLData& eglData, const KeyboardManager& km);

	
	void Init();


	void Tick(const float deltaTime);


	void Shutdown() {}


private:
	void AnimateModel(const bool loopAnimation = true);

	
	void Render();


	// Auto-initialized.
	Camera camera_{};

	// Ctor-initialized.
	const EGLData& eglData_;
	const KeyboardManager& km_;

	glm::mat4 modelMatrix_;
	glm::mat4 viewMatrix_;
	glm::mat4 projectionMatrix_;

	MD2Model md2Model_{};

	// Need at least these 2 variables to animate an md2 model. 
	// Should wrap in a struct with other values (position, etc) if multiple models exist.
	size_t currentAnimationIndex_{ 0 };
	MD2Model::AnimationState animationState_;
};