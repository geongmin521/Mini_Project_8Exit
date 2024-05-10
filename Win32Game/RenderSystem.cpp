#include "RenderSystem.h"
#include "SceneManager.h"
#include "globalheader.h"

RenderSystem* RenderSystem::Instance = nullptr;

RenderSystem::RenderSystem() 
	: _hdc(0),
	  _backDC(0),
	  _hWnd(0), 
	  _rect{},
	  _hInstance(0),
	  _MainBitmap(0),
	  _OldBitmap(0),
	  _Brush{},
	  _Pen{}
{
}

RenderSystem::~RenderSystem() {
	DeleteDC(_backDC);
	ReleaseDC(_hWnd, _hdc);
	DeleteObject(_MainBitmap);

	for (int i = 0; i < (int)PEN_TYPE::END; i++) {
		DeleteObject(_Pen[i]);
	}
}

RenderSystem* RenderSystem::GetInstance() {
	if (Instance == nullptr) {
		Instance = new RenderSystem();
	}
	return Instance;
}

void RenderSystem::DestroyInstance() {
	if (Instance != nullptr) {
		delete Instance;
		Instance = nullptr;
	}
}

void RenderSystem::CreateBrushPen()
{
	_Brush[(int)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

	_Pen[(int)PEN_TYPE::RED] = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	_Pen[(int)PEN_TYPE::GREEN] = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	_Pen[(int)PEN_TYPE::BLUE] = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}

void RenderSystem::InitRender() {
	_hInstance = global::GetWinApp().GetInstance();
	_hWnd = global::GetWinApp().GetWindow();
	_hdc = GetDC(_hWnd);
	_backDC = CreateCompatibleDC(_hdc);

	GetClientRect(_hWnd, &_rect);
	_MainBitmap = CreateCompatibleBitmap(_hdc, global::GetWinApp().GetWidth(), global::GetWinApp().GetHeight());
	_OldBitmap = (HBITMAP)SelectObject(_backDC, _MainBitmap);
	
	DeleteObject(_OldBitmap);

	CreateBrushPen();
}

void RenderSystem::StartDraw() {
	PatBlt(_backDC, 0, 0, global::GetWinApp().GetWidth(), global::GetWinApp().GetHeight(), WHITENESS);
}

void RenderSystem::EndDraw() {
	BitBlt(_hdc, 0, 0, global::GetWinApp().GetWidth(), global::GetWinApp().GetHeight(), _backDC, 0, 0, SRCCOPY);
}