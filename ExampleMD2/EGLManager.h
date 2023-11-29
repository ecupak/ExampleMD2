#pragma once

#include <EGL/egl.h>
#include <EGL/eglext.h>

#include <cstdio>


struct EGLData
{
	EGLData() = default;

	int width_{ 0 };
	int height_{ 0 };

	EGLDisplay display_{ NULL };
	EGLSurface surface_{ NULL };
	EGLContext context_{ NULL };

	EGLNativeWindowType nativeWindow_{ NULL };

	bool isReady_{ false };
};


class EGLManager
{
public:
	EGLManager(EGLData& eglData);


private:
	const EGLint CreateContext(EGLData& eglData);
	
	
	void ConfigureContext(EGLData& eglData);	
	
	
	void DisplayHardwareSettings();


	EGLData eglDisplay_;
	
	int majorVersion_;
	int minorVersion_;
};

