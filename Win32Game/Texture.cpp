#include "Texture.h"
#include "RenderSystem.h"

Texture::Texture() : _DC(0), _Bitmap(0), _BitInfo{}, _Image(0), _ImageSize{}
{
}

Texture::~Texture()
{
	DeleteDC(_DC);
	DeleteObject(_Bitmap);
	delete _Image;
}

void Texture::Load(const std::wstring& filepath)
{
	_Image = Image::FromFile(filepath.c_str());
	_ImageSize = { _Image->GetWidth(), _Image->GetHeight() };

	_DC = CreateCompatibleDC(renderSystem->_hdc);
	_Bitmap = (HBITMAP)LoadImage(nullptr, filepath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	HBITMAP old = (HBITMAP)SelectObject(_DC, _Bitmap);
	GetObject(_Bitmap, sizeof(BITMAP), &_BitInfo);

	DeleteObject(old);
}
