#include "Configuration.h"
#include "EGLManager.h"
#include "X11Input.h"
#include "MainLoop.h"


int main()
{
	// Data to hold gathered context information.
	EGLData eglData{};
	eglData.width_ = Configuration::ScreenWidth;
	eglData.height_ = Configuration::ScreenHeight;

	// Create X11 context.
	X11Input input{ eglData };

	// Create EGL context.
	EGLManager eglManager{ eglData };

	// Meat of the program.
	MainLoop mainLoop{ eglData, input };
	mainLoop.Run();

	// TODO: close egl and x11. Currently closes with seg fault.
}