#include "LobbyScene.h"
#include "LobbyUI.h"

LobbyScene::LobbyScene()
{

}

LobbyScene::~LobbyScene()
{
}

void LobbyScene::Start()
{
	LobbyUI* lobbyUI = new LobbyUI;
	AddObject(lobbyUI, LAYER_GROUP::UI);
}

void LobbyScene::End()
{
	SceneEnd();
}
