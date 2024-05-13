#pragma once
#include "GameResource.h"
#include "RenderSystem.h"

struct ImageSize {
	UINT width;
	UINT height;
};

class Texture : public GameResource {
public:
	void Load(const std::wstring& filepath);

	LONG Width() { return _ImageSize.width; }
	LONG Height() { return _ImageSize.height; }
	HDC GetDC() { return _DC; }
	Image* GetImage() const { return _Image; }

private:
	HDC _DC;
	HBITMAP _Bitmap;
	BITMAP _BitInfo;
	Image* _Image;
	ImageSize _ImageSize;

	Texture();
	~Texture();

	friend class ResourceManager;
};