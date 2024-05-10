#pragma once
#include "GameResource.h"
#include "RenderSystem.h"

class Texture : public GameResource {
public:
	void Load(const std::wstring& filepath);

	LONG Width() { return _BitInfo.bmWidth; }
	LONG Height() { return _BitInfo.bmHeight; }
	HDC GetDC() { return _DC; }

private:
	HDC _DC;
	HBITMAP _Bitmap;
	BITMAP _BitInfo;

	Texture();
	~Texture();

	friend class ResourceManager;
};