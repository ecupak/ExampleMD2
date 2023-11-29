#pragma once

#include "X11Input.h"
#include "EGLManager.h"

#include "Timer.h"
#include "Game.h"


class MainLoop
{
public:
	MainLoop(EGLData& eglData, X11Input& input);
	
	
	void Run();


private:
	void Init();


	// Auto-initialized.
	KeyboardManager km_{};
	Timer timer_{};

	// Ctor-initialized.
	EGLData& eglData_;
	X11Input& input_;
	Game game_;


	bool isGameRunning_{ true };
};

