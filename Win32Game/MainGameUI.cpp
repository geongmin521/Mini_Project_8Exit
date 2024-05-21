#include "MainGameUI.h"
#include "Camera.h"
#include "Button_Pause.h"

MainGameUI::MainGameUI()
{
	Button_Pause* buttonPause = new Button_Pause;
	buttonPause->_Parent = this;
	buttonPause->SetLocation(Vector3(100.0f, 80.0f, 0));
	_Child.push_back(buttonPause);

	SetName(L"MainUI");
}

MainGameUI::~MainGameUI()
{
	for (int i = 0; i < _Child.size(); i++) {
		delete _Child[i];
	}
}

void MainGameUI::Update()
{
	for (int i = 0; i < _Child.size(); i++) {
		_Child[i]->Update();
	}
}

void MainGameUI::Render()
{
	for (int i = 0; i < _Child.size(); i++) {
		_Child[i]->Render();
	}
}
