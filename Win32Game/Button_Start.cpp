#include "Button_Start.h"
#include "ResourceManager.h"
#include "SceneManager.h"

Button_Start::Button_Start() : _MyTex(nullptr), _Parent(nullptr), _FadeIn(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"Button_Start", L"Image\\UI\\Title_main.png");
	SetScale(Vector3((float)_MyTex->Width(), (float)_MyTex->Height(), 0));
	_FadeIn = new FadeIn;
}

Button_Start::~Button_Start()
{
}

void Button_Start::Update()
{
	SetLocation(_Pos);
	if (inputSystem->GetMouseButtonUp(0)) {
		if (CheckPositionOnUI(this) == true) {
			OnClick();
		}
	}
	if (_FadeIn->Enable()) {
		_FadeIn->Update();
	}
}

void Button_Start::Render()
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

void Button_Start::OnClick()
{
	_FadeIn->SetTargetScene(SCENE_LAYER::STORY);
	_FadeIn->SetEnable(true);
}
