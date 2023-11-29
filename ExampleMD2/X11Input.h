#pragma once

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "EGLManager.h"
#include "KeyboardManager.h"


class X11Input
{
public:
	X11Input(EGLData& eglData);
	~X11Input();

	
	void SetInputHandler(KeyboardManager* km);


	void Update();


private:
	void Init(EGLData& eglData);
	
	
	// X11 context.
	Display* display_;
	Window window_;
	GC graphicsContext_;

	
	// Input handler.
	KeyboardManager* km_{ nullptr };
};