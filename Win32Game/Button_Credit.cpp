#include "Button_Credit.h"
#include "SceneManager.h"

Button_Credit::Button_Credit() : _MyTex(nullptr), _Parent(nullptr), _Timer(0)
{
	_MyTex = resourceManager->GetTexture(L"Button_Credit", L"Image\\Button\\Button_Credit_Nomal.png");
	SetScale(Vector3((float)_MyTex->Width(), (float)_MyTex->Height(), 0));
}

Button_Credit::~Button_Credit()
{
}

void Button_Credit::Update()
{
	SetLocation(_Pos);

	if (CheckPositionOnUI(this)) {
		if (inputSystem->GetMouseButtonDown(0)) {
			_MyTex = resourceManager->GetTexture(L"Button_Credit_MouseClick", L"Image\\Button\\Button_Credit_Click.png");
		}
		else {
			_MyTex = resourceManager->GetTexture(L"Button_Credit_MouseOver", L"Image\\Button\\Button_Credit_Over.png");
		}
	}
	else {
		_MyTex = resourceManager->GetTexture(L"Button_Credit", L"Image\\Button\\Button_Credit_Nomal.png");
	}

	if (inputSystem->GetMouseButtonUp(0)) {
		if (CheckPositionOnUI(this) == true) {
			_StartTimer = true;
			camera->PlayEffect(FADE_IN);
		}
	}
	if (_StartTimer == true) {
		_Timer += timeManager->GetDeltaTime();
		if (_Timer >= 1.0f) {
			_Timer = 0;
			_StartTimer = false;
			OnClick();
		}
	}
}

void Button_Credit::Render()
{
	Graphics g(renderSystem->_backDC);
	int endX = (int)_MyTex->Width();
	int endY = (int)_MyTex->Height();

	g.DrawImage(_MyTex->GetImage(),
		(INT)_Pos._x - endX / 2, (INT)_Pos._y - endY / 2,
		endX, endY
	);
}

void Button_Credit::OnClick()
{
	sceneManager->LoadScene(SCENE_LAYER::CREDIT);
}
