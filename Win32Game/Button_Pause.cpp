#include "Button_Pause.h"
#include "ResourceManager.h"
#include "PauseUI.h"

Button_Pause::Button_Pause() : _MyTex(nullptr), _Parent(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"Button_Pause", L"Image\\Button\\Pause.png");
	SetScale(Vector3((float)_MyTex->Width(), (float)_MyTex->Height(), 0));
}

Button_Pause::~Button_Pause()
{
}

void Button_Pause::Update()
{
	_Pos = GetLocation() + _Parent->GetLocation();
	if (inputSystem->GetMouseButtonUp(0)) {
		if (CheckPositionOnUI(this) == true) {
			OnClick();
		}
	}
}

void Button_Pause::Render()
{
	Graphics g(renderSystem->_backDC);
	int endX = (int)_MyTex->Width();
	int endY = (int)_MyTex->Height();

	g.DrawImage(_MyTex->GetImage(),
		(INT)_Pos._x - endX / 2, (INT)_Pos._y - endY / 2,
		endX, endY
	);
}

void Button_Pause::OnClick()
{
	timeManager->SetTimeScale(0);
	GetUIObject(L"PauseUI")->SetEnable(true);
}
