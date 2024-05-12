#pragma once
#include "globalheader.h"

#define Window global::GetWinApp()
#define WindowWidth Window.GetWidth()
#define WindowHeight Window.GetHeight()
#define WindowHandle Window.GetWindow()
#define WindowInstance Window.GetInstance()

class WinApp
{
public:

	WinApp() = default;
	~WinApp() = default;

	void Initialize(HINSTANCE hInstance);

	void Run();

	void Finalize();

	HINSTANCE GetInstance() const { return m_hInstance; }

	HWND GetWindow() const { return m_hWnd; }

	const int GetWidth() const { return width; }
	const int GetHeight() const { return height; }

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:

	HINSTANCE m_hInstance = { 0 };  // HINSTANCE is a handle to an Instance of a module.
	HWND m_hWnd = { 0 };			// HWND is a handle to a window.

	int width = 1024;
	int height = 768;
};

namespace global
{
	const WinApp& GetWinApp();
}