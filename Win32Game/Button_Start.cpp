#include "Button_Start.h"
#include "ResourceManager.h"
#include "SceneManager.h"

Button_Start::Button_Start() : _MyTex(nullptr), _Parent(nullptr), _Timer(0)
{
	_MyTex = resourceManager->GetTexture(L"Button_Start", L"Image\\Button\\Button_Start_nomal.png");
	SetScale(Vector3((float)_MyTex->Width(), (float)_MyTex->Height(), 0));
}

Button_Start::~Button_Start()
{
}

void Button_Start::Update()
{
	SetLocation(_Pos);

	if (CheckPositionOnUI(this)) {
		if (inputSystem->GetMouseButtonDown(0)) {
			_MyTex = resourceManager->GetTexture(L"Button_Start_MouseClick", L"Image\\Button\\Button_Start_Click.png");
		}
		else {
			_MyTex = resourceManager->GetTexture(L"Button_Start_MouseOver", L"Image\\Button\\Button_Start_Over.png");
		}
	}
	else {
		_MyTex = resourceManager->GetTexture(L"Button_Start", L"Image\\Button\\Button_Start_nomal.png");
	}
	
	if (inputSystem->GetMouseButtonUp(0)) {
		if (CheckPositionOnUI(this) == true) {
			_StartTimer = true;
			camera->PlayEffect(FADE_IN);
			Music::soundManager->PlayMusic(Music::eSoundList::Buttoclick, Music::eSoundChannel::ButtonClick);//À½¾Ç Àç»ý
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

void Button_Start::Render()
{
	Graphics g(renderSystem->_backDC);
	int endX = (int)_MyTex->Width();
	int endY = (int)_MyTex->Height();

	g.DrawImage(_MyTex->GetImage(),
		(INT)_Pos._x - endX / 2, (INT)_Pos._y - endY / 2,
		endX, endY
	);
}

void Button_Start::OnClick()
{
	
	sceneManager->LoadScene(SCENE_LAYER::STORY);
}
