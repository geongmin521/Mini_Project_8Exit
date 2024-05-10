#include "InputSystem.h"

InputSystem* InputSystem::Instance = nullptr;

InputSystem::InputSystem()
{
	for (int i = 0; i < 256; i++) {
		_isKeyDown[i] = false;
		_isKeyUp[i] = false;
		_isKey[i] = false;
	}
	InitMouse();
}

InputSystem::~InputSystem()
{
	delete[] _isKeyDown;
	delete[] _isKeyUp;
	delete[] _isKey;
}

InputSystem* InputSystem::GetInstance()
{
	if (Instance == nullptr) {
		Instance = new InputSystem;
	}
	return Instance;
}

void InputSystem::DestroyInstance()
{
	delete Instance;
	Instance = nullptr;
}

void InputSystem::InitMouse()
{
	_curMouse._x = global::GetWinApp().GetWidth() / 2;
	_curMouse._y = global::GetWinApp().GetHeight() / 2;
	_curMouse._left = false;
	_curMouse._right = false;
	_curMouse._middle = false;

	_prevMouse = _curMouse;
	SetCursorPos(_curMouse._x, _curMouse._y);
}

void InputSystem::UpdateKey()
{
	HWND hWnd = GetFocus();
	if (hWnd != nullptr) {
		for (int i = 0; i < 256; i++) {
			if (GetAsyncKeyState(i) & 0x8000) {
				_isKeyDown[i] = true;
				_isKeyUp[i] = false;
				_isKey[i] = true;
			}
			if (GetAsyncKeyState(i) & 0x8001) {
				_isKeyDown[i] = false;
				_isKeyUp[i] = false;
				_isKey[i] = true;
			}
			if (GetAsyncKeyState(i) & 0x0001) {
				_isKeyDown[i] = false;
				_isKeyUp[i] = true;
				_isKey[i] = false;
			}
		}
	}
}

void InputSystem::UpdateMouse()
{
	_prevMouse = _curMouse;

	POINT pos;
	GetCursorPos(&pos);
	ScreenToClient(global::GetWinApp().GetWindow(), &pos);

	_curMouse._x = pos.x;
	_curMouse._y = pos.y;
	_curMouse._wheel = 0;
			  
	_curMouse._left = (GetKeyState(VK_LBUTTON) & 0x8000) != 0;
	_curMouse._right = (GetKeyState(VK_RBUTTON) & 0x8000) != 0;
	_curMouse._middle = (GetKeyState(VK_MBUTTON) & 0x8000) != 0;
}

void InputSystem::ResetInput() {
	for (int i = 0; i < 256; i++) {
		_isKeyDown[i] = false;
		_isKeyUp[i] = false;
		_isKey[i] = false;
	}
}