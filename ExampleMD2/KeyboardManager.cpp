#include "KeyboardManager.h"

#include <iostream>

KeyboardManager::KeyboardManager() {}


// Update the state of the keypackets.
void KeyboardManager::Update()
{
	for (KeyPacket& packet : keyPackets_)
	{
		bool wasHandled{ false };

		if (packet.wasPressed && !packet.wasReleased)
		{
			packet.isJustPressed = !packet.isPressed;
			packet.isPressed = true;
			packet.isJustReleased = false;
			wasHandled = true;
		}
		
		if (packet.wasReleased && !packet.wasPressed)
		{
			packet.isJustReleased = packet.isPressed;
			packet.isPressed = false;
			packet.isJustPressed = false;
			wasHandled = true;
		}

		if (!wasHandled)
		{
			packet.isJustPressed = false;
			packet.isJustReleased = false;
		}

		packet.Reset();
	}
}


// Setting keystate obtained by Game using GLFW keycodes.
void KeyboardManager::KeyPressed(const KeySym keycode)
{
	int index{ GetPacketIndex(keycode) };

	if (index != -1)
	{
		keyPackets_[index].wasPressed = true;
	}

	std::cout << "Pressed " << keycode << std::endl;
}


void KeyboardManager::KeyReleased(const KeySym keycode)
{
	int index{ GetPacketIndex(keycode) };

	if (index != -1)
	{
		keyPackets_[index].wasReleased = true;
	}

	std::cout << "Released " << keycode <<  '\n' << std::endl;
}


// Returning keystate to objects using Action enum.
const bool KeyboardManager::IsPressed(const Action action) const
{
	return keyPackets_[action].isPressed;
}


const bool KeyboardManager::IsJustPressed(const Action action) const
{
	return keyPackets_[action].isJustPressed;
}


const bool KeyboardManager::IsJustReleased(const Action action) const
{
	return keyPackets_[action].isJustReleased;
}


void KeyboardManager::SetKeyBinding(const Action, const int)
{
	
}


void KeyboardManager::ReleaseAll()
{
	for (int index{ 0 }; index < Action::Count; ++index)
	{
		keyPackets_[index].BigReset();
	}
}


void KeyboardManager::MouseMovedTo(const float x, const float y)
{
	mousePosition_ = { x, y };
}


float2 KeyboardManager::GetMousePosition() const
{
	return mousePosition_;
}


const int KeyboardManager::GetPacketIndex(const KeySym keycode) const
{
	for (int index{ 0 }; index < Action::Count; ++index)
	{
		if (keycode == keyPackets_[index].boundKeycode_ || keycode == keyPackets_[index].altKeycode_)
		{
			return index;
		}
	}

	return -1;
}