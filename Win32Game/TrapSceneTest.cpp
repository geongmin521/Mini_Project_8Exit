#include "TrapSceneTest.h"
#include "Camera.h"
#include "CollisionManager.h"
#include "InGameObjectHeader.h"
#include "DarkChange.h"
TrapSceneTest::TrapSceneTest() : _PrevTrapIdx(-1), _ObjectPlace(10, nullptr), _AnomalyObjects(10)
{
	//TODO: ���⼭ �� ���� �� ������Ʈ�� �����ؾ� �մϴ�.

	std::vector<Vector3> pos = resourceManager->GetMapPos(L"area1");
	for (int i = 0; i < pos.size(); i++)
	{
		//TODO: ���⼭ ������ �ν��Ͻ��� �������� �������ݴϴ�.
	}
	collisionManager->CheckGroup(LAYER_GROUP::PLAYER, LAYER_GROUP::MONSTER);
}

TrapSceneTest::~TrapSceneTest()
{
}

void TrapSceneTest::Start()
{
	//GameObject* bg = new BackGround;
	//bg->SetLocation(Vector3(-(float)(WindowWidth / 2), -(float)(WindowHeight / 2), 0));

	//
	//

	//
	//AddObject(spider1, LAYER_GROUP::MONSTER);

	//
	//AddObject(spider2, LAYER_GROUP::MONSTER);

	//GameObject* scareCrow = new ScareCrow;
	//AddObject(scareCrow, LAYER_GROUP::MONSTER);

	//GameObject* snake = new Snake;
	//AddObject(snake, LAYER_GROUP::MONSTER);

	//
	//AddObject(sunFlower, LAYER_GROUP::MONSTER);
	//
	//
	//AddObject(textBox, LAYER_GROUP::UI);
	GameObject* spider1 = new Spider1;
	_ObjectPlace[0] = spider1;
	GameObject* spider2 = new Spider2;
	_ObjectPlace[1] = spider2;
	GameObject* scareCrow = new ScareCrow;
	_ObjectPlace[2] = scareCrow;
	GameObject* snake = new Snake;
	_ObjectPlace[3] = snake;

	GameObject* bg = new BackGround;
	bg->SetLocation(Vector3(-(float)(WindowWidth / 2), -(float)(WindowHeight / 2), 0));
	AddObject(bg, LAYER_GROUP::BACKGROUND);

	GameObject* npc = new NPC;
	npc->SetEnable(true);
	AddObject(npc, LAYER_GROUP::TRAPTRIGGER);

	GameObject* dark = new DarkChange;
	dark->SetLocation(Vector3(0,0, 0));
	AddObject(dark, LAYER_GROUP::BACKGROUND);

	GameObject* player = new Player;
	player->SetLocation(Vector3(-800, 230, 0));
	AddObject(player, LAYER_GROUP::PLAYER);
	
	camera->SetTarget(player);

	InitObjectPlace();
}

void TrapSceneTest::End() 
{
	SceneEnd();
}

void TrapSceneTest::InitObjectPlace()
{
	//int idx;
	//while (true) {
	//	idx = GetRandomNum(sizeof(_AreaSet) / sizeof(int));
	//	if (_PrevTrapIdx != idx) break;
	//}
	//_PrevTrapIdx = idx;

	//int compareFlg = 1;
	//int areaSet = _AreaSet[_PrevTrapIdx];

	//// �̻������� �����ϴ� ������ ������Ʈ�� ����� ������ ������Ʈ�߿� �̾� ��ġ�մϴ�.
	//for (int shift = _ObjectPlace.size() - 1; shift >= 0; shift--) {
	//	if (areaSet & (compareFlg << shift)) {
	//		int areaIdx = _ObjectPlace.size() - 1 - shift;
	//		_ObjectPlace[areaIdx] = GetAnomalyObject(areaIdx);
	//	}
	//}

	//// �̻������� �����ϴ� ������ ������Ʈ�� �� ä���־����� ������ �������� ������ ������Ʈ�� ä��ϴ�.
	//for (int i = 0; i < _ObjectPlace.size(); i++) {
	//	if (_ObjectPlace[i] == nullptr) {
	//		_ObjectPlace[i] = _AnomalyObjects[i][0];
	//	}
	//}

	// �������� ������Ʈ�� �� ���ְ� ������Ʈ���� ���� ������ݴϴ�.
	for (int i = 0; i < _ObjectPlace.size(); i++) {
		if(_ObjectPlace[i] != nullptr) AddObject(_ObjectPlace[i], LAYER_GROUP::MONSTER);
	}
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
		
		������ ���� ������ ��� ������ ������ �ִ�.

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

GameObject* TrapSceneTest::GetAnomalyObject(int idx)
{
	int randomAnomaly = GetRandomNum(_AnomalyObjects[idx].size());
	return _AnomalyObjects[idx][randomAnomaly];
}