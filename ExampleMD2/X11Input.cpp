#include "X11Input.h"


X11Input::X11Input(EGLData& eglData)
{
	Init(eglData);
}


X11Input::~X11Input()
{
	XFreeGC(display_, graphicsContext_);
	XDestroyWindow(display_, window_);
	XCloseDisplay(display_);
}


void X11Input::Init(EGLData& eglData)
{
	unsigned int black{ 0x000000 };

	// Setup display/screen/window.
	display_ = XOpenDisplay(nullptr);
	window_ = XCreateSimpleWindow(display_, DefaultRootWindow(display_), 0, 0, eglData.width_, eglData.height_, 5, black, black);
	XSetStandardProperties(display_, window_, "MD2 Example", "AltTitle", None, NULL, 0, NULL);

	// Setup inputs.
	XSelectInput(display_, window_, ExposureMask | PointerMotionMask | ButtonPressMask | KeyPressMask | KeyReleaseMask);

	// Setup graphics context.
	graphicsContext_ = XCreateGC(display_, window_, 0, 0);
	XSetBackground(display_, graphicsContext_, black);
	XSetForeground(display_, graphicsContext_, black);
	XClearWindow(display_, window_);
	XMapRaised(display_, window_);
	XFlush(display_);

	// Store window in eglData for EGLContext creation.
	eglData.nativeWindow_ = static_cast<EGLNativeWindowType>(window_);
}


void X11Input::SetInputHandler(KeyboardManager* km)
{
	km_ = km;
}


void X11Input::Update()
{
	XEvent event;
	KeySym keySym;
	char text[25];

	// [Credit] Derived from Lasse's (220010) modified tmpl8.
	// And slightly modified further to use my keyboard manager.
	while (XEventsQueued(display_, QueuedAfterReading) > 0)
	{
		// Get input event.
		XNextEvent(display_, &event);

		// Check key up/down & mouse button/move events.
		switch (event.type)
		{
		case KeyPress:
			XLookupString(&event.xkey, text, 25, &keySym, nullptr);
			km_->KeyPressed(keySym);
			break;
		case KeyRelease:
			XLookupString(&event.xkey, text, 25, &keySym, nullptr);
			km_->KeyReleased(keySym);
			break;
		/*case ButtonPress:
			XSetForeground(display_, graphicsContext_, 0xFF0000);
			XDrawLine(display_, window_, graphicsContext_, 150, 150, event.xbutton.x, event.xbutton.y);
			break;*/
		case MotionNotify:
			km_->MouseMovedTo(event.xmotion.x, event.xmotion.y);
			break;
		default:
			break;
		}
	}

	km_->Update();
}