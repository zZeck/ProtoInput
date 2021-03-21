#include <windows.h>
#include "FakeMouseKeyboard.h"
#include "HwndSelector.h"

namespace Proto
{

FakeMouseState FakeMouseKeyboard::mouseState{};
FakeKeyboardState FakeMouseKeyboard::keyboardState{};

void FakeMouseKeyboard::AddMouseDelta(int dx, int dy)
{
	mouseState.x += dx;
	mouseState.y += dy;

	if (mouseState.x < 0)
		mouseState.x = 0;
	if (mouseState.y < 0)
		mouseState.y = 0;

	if (mouseState.x > HwndSelector::windowWidth)
		mouseState.x = HwndSelector::windowWidth;

	if (mouseState.y > HwndSelector::windowHeight)
		mouseState.y = HwndSelector::windowHeight;
}

void FakeMouseKeyboard::SetMousePos(int x, int y)
{
	mouseState.x = x;
	mouseState.y = y;

	if (mouseState.x < 0)
		mouseState.x = 0;
	if (mouseState.y < 0)
		mouseState.y = 0;

	if (mouseState.x > HwndSelector::windowWidth)
		mouseState.x = HwndSelector::windowWidth;

	if (mouseState.y > HwndSelector::windowHeight)
		mouseState.y = HwndSelector::windowHeight;
}

void FakeMouseKeyboard::ReceivedKeyPressOrRelease(int vkey, bool pressed)
{
	static_assert(keyboardState.keysState.size() == keyboardState.asyncKeysState.size());
	
	if (vkey >= 0 && vkey < keyboardState.keysState.size())
	{
		keyboardState.keysState[vkey] = pressed;

		if (pressed)
			keyboardState.asyncKeysState[vkey] = true;
	}
}

void FakeMouseKeyboard::ClearAsyncKeyState(int vkey)
{
	if (vkey >= 0 && vkey < keyboardState.asyncKeysState.size())
	{
		keyboardState.asyncKeysState[vkey] = false;
	}
}

bool FakeMouseKeyboard::IsKeyStatePressed(int vkey)
{
	if (vkey >= 0 && vkey < keyboardState.keysState.size())
	{
		if (vkey == VK_SHIFT)
			return keyboardState.keysState[VK_SHIFT] || keyboardState.keysState[VK_LSHIFT] || keyboardState.keysState[VK_RSHIFT];
		if (vkey == VK_CONTROL)
			return keyboardState.keysState[VK_CONTROL] || keyboardState.keysState[VK_LCONTROL] || keyboardState.keysState[VK_RCONTROL];
		if (vkey == VK_MENU)
			return keyboardState.keysState[VK_MENU] || keyboardState.keysState[VK_LMENU] || keyboardState.keysState[VK_RMENU];
		
		return keyboardState.keysState[vkey];
	}
	
	return false;
}

bool FakeMouseKeyboard::IsAsyncKeyStatePressed(int vkey)
{
	if (vkey >= 0 && vkey < keyboardState.asyncKeysState.size())
	{
		if (vkey == VK_SHIFT)
			return keyboardState.asyncKeysState[VK_SHIFT] || keyboardState.asyncKeysState[VK_LSHIFT] || keyboardState.asyncKeysState[VK_RSHIFT];
		if (vkey == VK_CONTROL)
			return keyboardState.asyncKeysState[VK_CONTROL] || keyboardState.asyncKeysState[VK_LCONTROL] || keyboardState.asyncKeysState[VK_RCONTROL];
		if (vkey == VK_MENU)
			return keyboardState.asyncKeysState[VK_MENU] || keyboardState.asyncKeysState[VK_LMENU] || keyboardState.asyncKeysState[VK_RMENU];
		
		return keyboardState.asyncKeysState[vkey];
	}

	return false;
}

}