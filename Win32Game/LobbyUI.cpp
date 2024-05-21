#include "LobbyUI.h"
#include "Button_Start.h"
#include "MainBG.h"

LobbyUI::LobbyUI()
{
	MainBG* bg = new MainBG;
	_Child.push_back(bg);

	Button_Start* btnStart = new Button_Start;
	btnStart->_Parent = this;
	btnStart->_Pos = Vector3(960.0f, 700.0f, 0.0f);
	_Child.push_back(btnStart);
}

LobbyUI::~LobbyUI()
{

}

void LobbyUI::Update()
{
	for (int i = 0; i < _Child.size(); i++) {
		_Child[i]->Update();
	}
}

void LobbyUI::Render()
{
	for (int i = 0; i < _Child.size(); i++) {
		_Child[i]->Render();
	}
}
