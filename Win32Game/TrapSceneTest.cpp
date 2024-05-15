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
	//TODO: 여기서 각 구역 별 오브젝트를 생성해야 합니다.
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
		
		같은 종류, 다른 구역에서 동시에 이상현상이 발생할 수 있음.
		-> 비트마스킹으로 정리.
		거미 : 4구역, 15종
		허수아비 : 2구역 3종
		해바라기 : 2구역 3종
		마차 : 1구역 1종
		오두막 : 1구역 1종

		이상현상 구역을 정하는 방법 - 비트마스킹

		거미 구역			: 0b1001000101
		해바라기 구역		: 0b0100010000
		허수아비 구역		: 0b0010000010
		마차 구역			: 0b0000100000
		오두막 구역			: 0b0000001000

		5개 중에 랜덤 선택

		선택된 구역을 쉬프트 연산으로 돌면서 & == true 면 확률에 따른 오브젝트 선택후 AddObject.
		정상적인 현상은 무조건 각 구역의 0번 자리에 존재.

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