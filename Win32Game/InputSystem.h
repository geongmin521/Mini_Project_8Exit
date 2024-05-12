#pragma once
#include "Win32GameProject.h"

#define inputSystem InputSystem::GetInstance()

class InputSystem
{
public:
	InputSystem();
	~InputSystem();

	static InputSystem* GetInstance();
	void DestroyInstance();
	void ResetInput();
	void UpdateKey();
	bool isKeyDown(const unsigned int key) const { return _isKeyDown[key]; }
	bool isKeyUp(const unsigned int key) const { return _isKeyUp[key]; }
	bool isKey(const unsigned int key) const { return _isKey[key]; }

	class MouseState {
	public:
		int _x;
		int _y;
		int _wheel;
		bool _left;
		bool _right;
		bool _middle;
		
		MouseState() {
			_x = 0;
			_y = 0;
			_wheel = 0;
			_left = false;
			_right = false;
			_middle = false;
		}
	};

	void InitMouse();
	void UpdateMouse();
	const MouseState& GetMouseState() const { return _curMouse; }
	const MouseState& GetPrevMouseState() const { return _prevMouse; }
	bool isSame(const MouseState& a, const MouseState& b){ 
		return
			a._x == b._x &&
			a._y == b._y &&
			a._wheel == b._wheel &&
			a._left == b._left &&
			a._right == b._right &&
			a._middle == b._middle;
	}

private:
	static InputSystem* Instance;
	MouseState _curMouse;
	MouseState _prevMouse;
	bool _isKeyDown[256];
	bool _isKeyUp[256];
	bool _isKey[256];
};

