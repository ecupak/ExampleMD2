#include "MainLoop.h"

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>


#include <iostream>


MainLoop::MainLoop(EGLData& eglData, X11Input& input)
	: eglData_{ eglData }
	, input_{ input }
	, game_{ eglData, km_ }
{
	Init();
}


void MainLoop::Init()
{
	input_.SetInputHandler(&km_);
	
	game_.Init();
}


// [Credit] Inspired by Brian's tmpl8.
void MainLoop::Run()
{
	timer_.Reset();

	while (isGameRunning_)
	{	
		// Get delta time.
		float deltaTime(timer_.GetElapsed());
		timer_.Reset();

		// Input.
		input_.Update();

		// Quit?
		isGameRunning_ = !km_.IsPressed(Action::Quit);

		// Game tick.
		game_.Tick(deltaTime);
		
		// Swap buffers.
		glFlush();
		eglSwapBuffers(eglData_.display_, eglData_.surface_);
	}

	// TODO: release any memory in game.
	game_.Shutdown();
};