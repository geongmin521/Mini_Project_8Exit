#include "TrapSceneTest.h"
#include "Camera.h"
#include "BackGround.h"
#include "Player.h"
#include "Trap1.h"
#include "CollisionManager.h"
#include "TextBox.h"

TrapSceneTest::TrapSceneTest()
{
}

TrapSceneTest::~TrapSceneTest()
{
}

void TrapSceneTest::Start()
{
	GameObject* bg = new BackGround;
	bg->SetLocation(Vector3(-(float)(WindowWidth / 2), -(float)(WindowHeight / 2), 0));
	AddObject(bg, LAYER_GROUP::BACKGROUND);

	GameObject* player = new Player;
	AddObject(player, LAYER_GROUP::PLAYER);

	GameObject* textBox = new TextBox;
	textBox->SetLocation(Vector3(200,200, 0));
	AddObject(textBox, LAYER_GROUP::UI);

	collisionManager->CheckGroup(LAYER_GROUP::PLAYER, LAYER_GROUP::MONSTER);

	camera->SetTarget(player);
}

void TrapSceneTest::End() 
{
	SceneEnd();
}
