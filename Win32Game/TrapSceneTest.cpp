#include "TrapSceneTest.h"
#include "Camera.h"
#include "BackGround.h"
#include "Player.h"
#include "Spider1.h"
#include "CollisionManager.h"
#include "TrapManager.h"
#include "Spider2.h"
#include "SunFlower.h"
#include "TextBox.h"
#include "Snake.h"

TrapSceneTest::TrapSceneTest() : _PrevTrapIdx(-1), _ObjectPlace(10, nullptr), _AnomalyObjects(10)
{
	//TODO: 여기서 각 구역 별 오브젝트를 생성해야 합니다.
	std::vector<Vector3> pos = resourceManager->GetMapPos(L"area1");
	for (int i = 0; i < pos.size(); i++)
	{
		//TODO: 여기서 생성된 인스턴스의 포지션을 설정해줍니다.
	}
	
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

	GameObject* snake = new Snake;
	AddObject(snake, LAYER_GROUP::MONSTER);

	GameObject* sunFlower = new SunFlower;
	AddObject(sunFlower, LAYER_GROUP::MONSTER);
	GameObject* textBox = new TextBox;
	textBox->SetLocation(Vector3(200,200, 0));
	AddObject(textBox, LAYER_GROUP::UI);

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
		idx = GetRandomNum(sizeof(_AreaSet) / sizeof(int));
		if (_PrevTrapIdx != idx) break;
	}
	_PrevTrapIdx = idx;

	int compareFlg = 1;
	int areaSet = _AreaSet[_PrevTrapIdx];

	// 이상현상이 존재하는 구역의 오브젝트중 정상과 비정상 오브젝트중에 뽑아 배치합니다.
	for (int shift = _ObjectPlace.size() - 1; shift >= 0; shift--) {
		if (areaSet & (compareFlg << shift)) {
			int areaIdx = _ObjectPlace.size() - 1 - shift;
			_ObjectPlace[areaIdx] = GetAnomalyObject(areaIdx);
		}
	}

	// 이상현상이 존재하는 구역의 오브젝트를 다 채워넣었으면 나머지 정상적인 구역의 오브젝트도 채웁니다.
	for (int i = 0; i < _ObjectPlace.size(); i++) {
		if (_ObjectPlace[i] == nullptr) {
			_ObjectPlace[i] = _AnomalyObjects[i][0];
		}
	}

	// 랜더링과 업데이트를 할 수있게 오브젝트들을 씬에 등록해줍니다.
	for (int i = 0; i < _ObjectPlace.size(); i++) {
		AddObject(_ObjectPlace[i], LAYER_GROUP::MONSTER);
	}
	//TODO: idx의 값에 따라 오브젝트들을 심어야 합니다.
	/*
	*   총 8개의 스테이지
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
		
		레벨에 따라 등장할 기믹 개수는 정해져 있다.

		충돌이 있는 오브젝트의 구분은 각각의 OnCollision 함수들에서 시행. 모두 같은 레이어.

		이후 오브젝트들 랜더링, 업데이트.

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