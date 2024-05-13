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
}
