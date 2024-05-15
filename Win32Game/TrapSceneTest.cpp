#include "TrapSceneTest.h"
#include "Camera.h"
#include "BackGround.h"
#include "Player.h"
#include "Spider1.h"
#include "CollisionManager.h"
#include "TrapManager.h"
#include "Spider2.h"
#include "SunFlower.h"


TrapSceneTest::TrapSceneTest() : _PrevTrapIdx(-1), _ObjectPlace(10, nullptr), _AnomalyObjects(10)
{
	//TODO: ���⼭ �� ���� �� ������Ʈ�� �����ؾ� �մϴ�.
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
	player->SetLocation(Vector3(-800, 230, 0));
	AddObject(player, LAYER_GROUP::PLAYER);

	GameObject* spider1 = new Spider1;
	spider1->SetEnable(true);
	AddObject(spider1, LAYER_GROUP::MONSTER);

	GameObject* spider2 = new Spider2;
	spider2->SetEnable(true);
	AddObject(spider2, LAYER_GROUP::MONSTER);

	//GameObject* trap2 = new Trap2;
	//AddObject(trap2, LAYER_GROUP::BACKUNIT);

	GameObject* sunFlower = new SunFlower;
	AddObject(sunFlower, LAYER_GROUP::MONSTER);

	collisionManager->CheckGroup(LAYER_GROUP::PLAYER, LAYER_GROUP::MONSTER);
	collisionManager->CheckGroup(LAYER_GROUP::PLAYER, LAYER_GROUP::TRAPTRIGGER);
	collisionManager->CheckGroup(LAYER_GROUP::PLAYER, LAYER_GROUP::BACKUNIT);

	camera->SetTarget(player);

}

void TrapSceneTest::End()
{
	SceneEnd();
}

void TrapSceneTest::InitObjectPlace()
{
	int idx;
	while (true) {
		idx = GetRandomNum(5);
		if (_PrevTrapIdx != idx) break;
	}
	_PrevTrapIdx = idx;

	//TODO: idx�� ���� ���� ������Ʈ���� �ɾ�� �մϴ�.
	/*
	*   �� 8���� ��������
		0 : Spider		
		1 : SunFlower	
		2 : ScareCrow	
		3 : Spider		
		4 : HorseCar		
		5 : SunFlower	
		6 : WoodHouse	
		7 : Spider		
		8 : ScareCrow	
		9 : Spider		
		
		���� ����, �ٸ� �������� ���ÿ� �̻������� �߻��� �� ����.
		-> ��Ʈ����ŷ���� ����.
		�Ź� : 4����, 15��
		����ƺ� : 2���� 3��
		�عٶ�� : 2���� 3��
		���� : 1���� 1��
		���θ� : 1���� 1��

		�̻����� ������ ���ϴ� ��� - ��Ʈ����ŷ

		�Ź� ����			: 1001000101
		�عٶ�� ����		: 0100010000
		����ƺ� ����		: 0010000010
		���� ����			: 0000100000
		���θ� ����			: 0000001000

		5�� �߿� ���� ����

		���õ� ������ ����Ʈ �������� ���鼭 & == true �� Ȯ���� ���� ������Ʈ ������ AddObject.
		�浹�� �ִ� ������Ʈ�� ������ ������ OnCollision �Լ��鿡�� ����. ��� ���� ���̾�.

		���� ������Ʈ�� ������, ������Ʈ.

	*/

}

int TrapSceneTest::GetRandomNum(int size)
{
	std::random_device rd;
	std::mt19937_64 mt(rd());
	std::uniform_int_distribution<int> dist(0, size - 1);
	return dist(mt);
}

void TrapSceneTest::SetCompleteTrap(int idx)
{
	_CompleteTrap.insert({ idx, true });
}

bool TrapSceneTest::GetCompleteTrap(int idx)
{
	if (_CompleteTrap.find(idx) == _CompleteTrap.end()) {
		return false;
	}
	else {
		return true;
	}
}

