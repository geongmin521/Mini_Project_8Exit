#include "DarkChange.h"
#include "TimeSystem.h"
#include "ResourceManager.h"
#include "InputSystem.h"
#include "Camera.h"
#include <random>
#include <gdiplus.h>

#pragma comment(lib, "gdiplus.lib")
DarkChange::DarkChange() :_MyTex(nullptr), _Min(1.0f), _Down(1.0f / 60.0f), _cachedBitmap(nullptr), _graphics(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"DarkChange", L"Image\\Dark_Change.bmp");
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Initialize graphics object
	HDC hdc = GetDC(NULL);
	_graphics = new Gdiplus::Graphics(hdc);

	// Create the cached bitmap
	CreateCachedBitmap();

	ReleaseDC(NULL, hdc);
}

DarkChange::~DarkChange()
{

}


void DarkChange::Update()
{
	
	
}

void DarkChange::Render()
{
	Vector3 renderPosition = camera->GetRenderPos(GameObject::GetLocation());

	if (_cachedBitmap)
	{
		int startX = static_cast<int>(renderPosition._x) - _cachedBitmapWidth / 2;
		int startY = static_cast<int>(renderPosition._y) - _cachedBitmapHeight / 2;

		_graphics->DrawCachedBitmap(_cachedBitmap, startX, startY);
	}
}

void DarkChange::Min()
{
	_Min -= _Down * timeManager->GetDeltaTime();

	if (_Min < 0.0f)
		_Min = 0.0f;
}
//보라색 빼는 함수


void DarkChange::die()
{

}
//플레이어가 죽었을 때 이미지 작아짐

//플레이어 죽는 연결 함수

//
void DarkChange::CreateCachedBitmap()
{
	int width = _MyTex->Width();
	int height = _MyTex->Height();

	Bitmap tmpBit(width, height, PixelFormat32bppARGB);
	Graphics* pMemGraphics = Graphics::FromImage(&tmpBit);

	Color transColor(255, 0, 255); // 보라색을 투명하게
	ColorMap colorMap;
	colorMap.oldColor = transColor;
	colorMap.newColor = Color(0, 0, 0, 0); // 투명한 색으로 대체

	ImageAttributes imgAttr;
	imgAttr.SetRemapTable(1, &colorMap, ColorAdjustTypeBitmap);
	imgAttr.SetColorKey(transColor, transColor, ColorAdjustTypeBitmap);

	pMemGraphics->DrawImage(_MyTex->GetImage(),
		Rect(0, 0, width, height),
		0, 0, width, height, UnitPixel, &imgAttr);

	delete pMemGraphics;

	_cachedBitmap = new CachedBitmap(&tmpBit, _graphics);

	// Store the dimensions of the cached bitmap
	_cachedBitmapWidth = width;
	_cachedBitmapHeight = height;
}