#pragma once
#include "Win32GameProject.h"
#include "globalheader.h"
#define IGNORE_RenderSYSTEM


class RenderSystem
{
public:
	HDC _hdc;
	HDC _backDC;
	HWND _hWnd;
	RECT _rect;
	HINSTANCE _hInstance;
	HBITMAP _MainBitmap;
	HBITMAP _OldBitmap;

	RenderSystem();
	~RenderSystem();

	static RenderSystem* GetInstance();
	static void DestroyInstance();

	void CreateBrushPen();
	void InitRender();

	void StartDraw();
	void EndDraw();

	HBRUSH GetBrush(BRUSH_TYPE brush) const { return _Brush[(int)brush]; };
	HPEN GetPen(PEN_TYPE pen) const { return _Pen[(int)pen]; }

private:
	static RenderSystem* Instance;

	HBRUSH _Brush[(int)BRUSH_TYPE::END];
	HPEN _Pen[(int)PEN_TYPE::END];
};