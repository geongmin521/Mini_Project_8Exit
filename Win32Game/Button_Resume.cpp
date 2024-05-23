#include "Button_Resume.h"
#include "ResourceManager.h"

Button_Resume::Button_Resume() : _MyTex(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"Button_Resume", L"Image\\Button\\Button_Resume.png");
	SetScale(Vector3((float)_MyTex->Width(), (float)_MyTex->Height(), 0));
}

Button_Resume::~Button_Resume()
{
}

void Button_Resume::Update()
{
	SetLocation(_Pos);
	if (inputSystem->GetMouseButtonUp(0)) {
		if (CheckPositionOnUI(this) == true) {
			OnClick();
		}
	}
}

void Button_Resume::Render()
{
	Graphics g(renderSystem->_backDC);
	int endX = (int)_MyTex->Width();
	int endY = (int)_MyTex->Height();

	g.DrawImage(_MyTex->GetImage(),
		(INT)_Pos._x - endX / 2, (INT)_Pos._y - endY / 2,
		endX, endY
	);
}

void Button_Resume::OnClick()
{
	Music::soundManager->PlayMusic(Music::eSoundList::Buttoclick, Music::eSoundChannel::ButtonClick);//À½¾Ç Àç»ı
	timeManager->SetTimeScale(1.0f);
	_Parent->SetEnable(false);
}
