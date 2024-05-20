#include "PauseUI.h"
#include "PauseBG.h"
#include "Button_Title.h"
#include "Button_Resume.h"

PauseUI::PauseUI()
{
	PauseBG* bg = new PauseBG;
	bg->_Parent = this;
	_Child.push_back(bg);

	Button_Resume* btnResume = new Button_Resume;
	btnResume->_Parent = this;
	btnResume->_Pos = (Vector3(960.0f, 500.0f, 0.0f));
	_Child.push_back(btnResume);

	Button_Title* btnTitle = new Button_Title;
	btnTitle->_Parent = this;
	btnTitle->_Pos = (Vector3(960.0f, 700.0f, 0.0f));
	_Child.push_back(btnTitle);

	SetName(L"PauseUI");
}

PauseUI::~PauseUI()
{
}

void PauseUI::Update()
{
	for (int i = 0; i < _Child.size(); i++) {
		_Child[i]->Update();
	}
}

void PauseUI::Render()
{
	for (int i = 0; i < _Child.size(); i++) {
		_Child[i]->Render();
	}
}
