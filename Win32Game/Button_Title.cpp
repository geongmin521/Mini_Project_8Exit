#include "Button_Title.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "FadeIn.h"

Button_Title::Button_Title() : _MyTex(nullptr), _Parent(nullptr), _FadeIn(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"Button_Title", L"Image\\Button\\Button_Title.png");
	SetScale(Vector3((float)_MyTex->Width(), (float)_MyTex->Height(), 0));
	_FadeIn = new FadeIn;
}

Button_Title::~Button_Title()
{
	delete _FadeIn;
}

void Button_Title::Update()
{
	SetLocation(_Pos);
	if (inputSystem->GetMouseButtonUp(0)) {
		if (CheckPositionOnUI(this) == true) {
			timeManager->SetTimeScale(1.0f);
			OnClick();
		}
	}
	if (_FadeIn->Enable()) {
		_FadeIn->Update();
	}
}

void Button_Title::Render()
{
	Graphics g(renderSystem->_backDC);
	int endX = (int)_MyTex->Width();
	int endY = (int)_MyTex->Height();

	g.DrawImage(_MyTex->GetImage(),
		(INT)_Pos._x - endX / 2, (INT)_Pos._y - endY / 2,
		endX, endY
	);
	if (_FadeIn->Enable()) {
		_FadeIn->Render();
	}
}

void Button_Title::OnClick()
{
	_FadeIn->SetTargetScene(SCENE_LAYER::MAIN);
	_FadeIn->SetEnable(true);
}
