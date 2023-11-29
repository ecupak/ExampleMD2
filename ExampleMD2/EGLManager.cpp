#include "EGLManager.h"

#include <GLES3/gl31.h>


EGLManager::EGLManager(EGLData& eglData)
{
	eglData.isReady_ = (CreateContext(eglData) == EGL_SUCCESS);

	if (eglData.isReady_)
	{
		ConfigureContext(eglData);
		DisplayHardwareSettings();
	}
}


const EGLint  EGLManager::CreateContext(EGLData& eglData)
{
	// Get display.
	EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	if (display == EGL_NO_DISPLAY)
	{
		printf("eglGetDisplay error");
		return EGL_BAD_DISPLAY;	// Use closest matching error as value.
	}

	// Initialize EGL
	if (!eglInitialize(display, &majorVersion_, &minorVersion_))
	{
		printf("eglInitialize error");
		EGLint err = eglGetError();
		return err;
	}

	// Get configs
	EGLint numConfigs;
	if (!eglGetConfigs(display, NULL, 1, &numConfigs))
	{
		printf("eglGetConfigs error");
		EGLint err = eglGetError();
		return err;
	}

	// Setup config attribute list.
	const EGLint congifAttributeList[] =
	{
		EGL_RED_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_BLUE_SIZE, 8,
		EGL_ALPHA_SIZE, 8,
		EGL_DEPTH_SIZE, 8, // << this is a useful one to reseach
		EGL_SURFACE_TYPE,
		EGL_WINDOW_BIT,
		EGL_SAMPLE_BUFFERS, 1,		// TODO: Set this to 0 to see speed difference. Will disable antialiasing.
		EGL_SAMPLES, 4,
		EGL_NONE
	};

	// Choose config
	EGLConfig config;
	if (!eglChooseConfig(display, congifAttributeList, &config, 1, &numConfigs))
	{
		printf("eglChooseConfig error");
		EGLint err = eglGetError();
		return err;
	}

	// Setup context attribute list.
	const EGLint contextAttributeList[] =
	{
		EGL_CONTEXT_CLIENT_VERSION, 2,
			EGL_NONE
	};

	// Get context.
	EGLContext context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttributeList);
	if (context == EGL_NO_CONTEXT)
	{
		printf("eglCreateContext error");
		EGLint err = eglGetError();
		return err;
	}

	// Create a surface using X11 window.
	EGLSurface surface = eglCreateWindowSurface(display, config, eglData.nativeWindow_, NULL);
	if (surface == EGL_NO_SURFACE)
	{
		printf("eglCreateWindowSurface error");
		EGLint err = eglGetError();
		return err;
	}

	// Make the context current
	if (!eglMakeCurrent(display, surface, surface, context))
	{
		printf("eglMakeCurrent error");
		EGLint err = eglGetError();
		return err;
	}

	// Assign data to output var.
	eglData.display_ = display;
	eglData.surface_ = surface;
	eglData.context_ = context;

	return EGL_SUCCESS;
}


void EGLManager::ConfigureContext(EGLData& eglData)
{
	glViewport(0, 0, eglData.width_, eglData.height_);

	// Some OpenGLES2.0 states that we might need
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glDepthRangef(0.0f, 1.0f);
	glClearDepthf(1.0f);
	glCullFace(GL_BACK);

	//these are the options you can have for the depth, play with them?
	//#define GL_NEVER                          0x0200
	//#define GL_LESS                           0x0201
	//#define GL_EQUAL                          0x0202
	//#define GL_LEQUAL                         0x0203
	//#define GL_GREATER                        0x0204
	//#define GL_NOTEQUAL                       0x0205
	//#define GL_GEQUAL                         0x0206
}


void EGLManager::DisplayHardwareSettings()
{
	printf("This SBC supports version %i.%i of EGL\n", majorVersion_, minorVersion_);

	printf("This GPU supplied by  :%s\n", glGetString(GL_VENDOR));
	printf("This GPU supports     :%s\n", glGetString(GL_VERSION));
	printf("This GPU Renders with :%s\n", glGetString(GL_RENDERER));
	printf("This GPU supports     :%s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	int t; // Helper var to extract data.
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &t);
	printf("This GPU MaxTexSize is    :%i\n", t);
	
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &t);	
	printf("This GPU supports %i Texture units\n", t); // pi4 16

	printf("This GPU supports these extensions	:%s\n", glGetString(GL_EXTENSIONS));
}