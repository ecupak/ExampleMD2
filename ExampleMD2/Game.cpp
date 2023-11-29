#include "Game.h"

#include <stdexcept>
#include <iostream>

#include <glm/glm/gtc/matrix_transform.hpp>

#include "ShaderManager.h"
#include "ShaderProgramManager.h"


Game::Game(const EGLData& eglData, const KeyboardManager& km)
	: eglData_{ eglData }
	, km_{ km }
{	}


void Game::Init()
{
	auto& sm = ShaderManager::getInstance();
	auto& spm = ShaderProgramManager::getInstance();

	sm.loadVertexShader("md2", "assets/shaders/basic.vert");
	sm.loadFragmentShader("md2", "assets/shaders/basic.frag");

	auto& md2ShaderProgram = spm.createShaderProgram("md2");
	md2ShaderProgram.addShaderToProgram(sm.getVertexShader("md2"));
	md2ShaderProgram.addShaderToProgram(sm.getFragmentShader("md2"));

	spm.linkAllPrograms();

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

	// md2 models are usually loaded facing the ground as their default. 
	// This positions it so it is oriented up and fits the view better.
	modelMatrix_ = glm::mat4{ 1.0f };
	modelMatrix_ = glm::translate(modelMatrix_, glm::vec3{ 0.0f, -12.0f, 0.0f });
	modelMatrix_ = glm::rotate(modelMatrix_, glm::radians(180.0f), glm::vec3{ 0.0f, 1.0f, 0.0f }); // If you swap the rotation order
	modelMatrix_ = glm::rotate(modelMatrix_, glm::radians(-90.0f), glm::vec3{ 1.0f, 0.0f, 0.0f }); // you get gimble lock.
	modelMatrix_ = glm::scale(modelMatrix_, glm::vec3{ 0.2f, 0.2f, 0.2f });
	md2Model_.loadModel("assets/models/warrior/warrior.md2", modelMatrix_);

	// Start animating.
	AnimateModel();
}


void Game::Tick(const float deltaTime)
{
	camera_.Update(deltaTime, km_);

	// [Credit] https://github.com/michalbb1/opengl4-tutorials-mbsoftworks
	// Finding the next/prev animation index.
	if (km_.IsJustPressed(Action::NextAnimation))
	{
		currentAnimationIndex_ = (currentAnimationIndex_ + 1) % md2Model_.getAnimationNames().size();
		AnimateModel();
	}
	else if (km_.IsJustPressed(Action::PreviousAnimation))
	{
		currentAnimationIndex_ = (currentAnimationIndex_ + md2Model_.getAnimationNames().size() - 1) % md2Model_.getAnimationNames().size();
		AnimateModel();
	}

	animationState_.updateAnimation(deltaTime);

	Render();
}


void Game::AnimateModel(const bool loopAnimation)
{
	animationState_ = MD2Model::AnimationState{};
	animationState_ = md2Model_.startAnimation(md2Model_.getAnimationNames().at(currentAnimationIndex_), loopAnimation);
}


void Game::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	const auto& spm = ShaderProgramManager::getInstance();
	auto& md2Program = spm.getShaderProgram("md2");
	
	md2Program.useProgram();
	md2Program[ShaderConstants::projectionMatrix()] = glm::perspective(glm::radians(camera_.fov_), 1.0f * eglData_.width_ / eglData_.height_, 0.1f, 100.0f);
	md2Program[ShaderConstants::viewMatrix()] = camera_.GetViewMatrix();
	
	modelMatrix_ = glm::mat4{ 1.0f };
	modelMatrix_ = glm::translate(modelMatrix_, glm::vec3{ -5.0f, 0.0f, 0.0f });
	md2Program.setModelAndNormalMatrix(modelMatrix_);
	//md2Model_.renderModelStatic(); // Uncomment if you want to see a 2nd model that stays in the 1st frame of the 1st animation.

	modelMatrix_ = glm::mat4{ 1.0f };
	modelMatrix_ = glm::translate(modelMatrix_, glm::vec3{ 5.0f, 0.0f, 0.0f });
	md2Program.setModelAndNormalMatrix(modelMatrix_);
	md2Model_.renderModelAnimated(animationState_);
}