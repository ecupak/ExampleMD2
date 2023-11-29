#pragma once

#include <X11/keysym.h>
#include <X11/Xlib.h>


struct float2
{
	float x_{ 0.0f };
	float y_{ 0.0f };
};


struct KeyPacket
{
	KeyPacket(const KeySym boundKeycode, const KeySym altKeycode = XK_emptyset)
		: boundKeycode_{ boundKeycode }
		, altKeycode_{ altKeycode == XK_emptyset ? boundKeycode : altKeycode }
	{	}

	
	KeySym boundKeycode_{ 0 };
	KeySym altKeycode_{ 0 };


	void Reset()
	{
		wasPressed = false;
		wasReleased = false;
	}


	void BigReset()
	{
		wasPressed = false;
		wasReleased = false;
		
		isPressed = false;
		isJustPressed = false;
		isJustReleased = false;
	}


	bool wasPressed{ false };
	bool wasReleased{ false };

	bool isPressed{ false };
	
	bool isJustPressed{ false };
	bool isJustReleased{ false };
};


// These actions are tied to the keyPackets of corresponding index.
// keyPackets_[0] will be the first action, etc.
enum Action
{
	Left,
	Right,
	Up,
	Down,

	NextAnimation,
	PreviousAnimation,

	TogglePrimaryAxis,
	ToggleRotationMode,

	Quit,

	Count,
	NoAction,
};


class KeyboardManager
{
public:
	KeyboardManager();

	void Update();

	void KeyPressed(const KeySym keycode);

	void KeyReleased(const KeySym keycode);

	const bool IsPressed(const Action action) const;

	const bool IsJustPressed(const Action action) const;

	const bool IsJustReleased(const Action action) const;

	void SetKeyBinding(const Action action, const int newKeycode);

	void ReleaseAll();

	void MouseMovedTo(const float x, const float y);

	float2 GetMousePosition() const;


private:
	const int GetPacketIndex(const KeySym keycode) const;

	// Initial keybinding should match the action of the keyPacket.
	// keyPackets_[0] is the first action and should have a corresponding keybinding.
	// Provide a 2nd keybinding if the action has an alternate key binding.
	KeyPacket keyPackets_[Action::Count]
	{
		// Move (has upper/lower case pairs because holding shift + wasd gives different effect but also changes they keycode).
		{ XK_a, XK_A },
		{ XK_d, XK_D },
		{ XK_w, XK_W },
		{ XK_s, XK_S },

		// Animation next/prev.
		XK_Right,
		XK_Left,

		// Toggle between Z and Y axis strafing.
		XK_Shift_L,
		
		// Toggle rotation mode (simulates mouse movement).
		XK_space,

		// Exit
		XK_Escape,
	};

	// Yes, temporarily housing the mouse position in the keyboard manager for now.
	float2 mousePosition_{ 0.0f, 0.0f };
};