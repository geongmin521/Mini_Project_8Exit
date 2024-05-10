#include "Texture.h"
#include "RenderSystem.h"

Texture::Texture() : _DC(0), _Bitmap(0), _BitInfo{}
{
}

Texture::~Texture()
{
	DeleteDC(_DC);
	DeleteObject(_Bitmap);
}

void Texture::Load(const std::wstring& filepath)
{
	//TODO: 여기에 이미지를 로드해 갖고오는 코드를 만들어야 합니다.
	_DC = CreateCompatibleDC(RenderSystem::GetInstance()->_hdc);
	_Bitmap = (HBITMAP)LoadImage(nullptr, filepath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(_Bitmap, sizeof(BITMAP), &_BitInfo);

	HBITMAP old = (HBITMAP)SelectObject(_DC, _Bitmap);
	DeleteObject(old);
}
