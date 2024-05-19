#include "TrapSceneTest.h"
#include "Camera.h"
#include "CollisionManager.h"
#include "InGameObjectHeader.h"

TrapSceneTest::TrapSceneTest() : _PrevTrapIdx(-1), _ObjectPlace(6), _AnomalyObjects(6), _AreaWidth(3840), _StageNum(6), _AreaSettingState{}
{
	//TODO: 여기서 각 구역 별 오브젝트를 생성해야 합니다.
	std::vector<Vector3> pos = resourceManager->GetMapPos(L"area1");
	for (int i = 0; i < pos.size(); i++)
	{
		//TODO: 여기서 생성된 인스턴스의 포지션을 설정해줍니다.
	}
	collisionManager->CheckGroup(LAYER_GROUP::PLAYER, LAYER_GROUP::MONSTER);
	collisionManager->CheckGroup(LAYER_GROUP::PLAYER, LAYER_GROUP::SEARCH);
}

TrapSceneTest::~TrapSceneTest()
{
}

void TrapSceneTest::Start()
{
	//=============
	//	1구역 : spider
	//=============
	for (int i = 0; i < 6; i++) {
		GameObject* spider = new Spider1;
		_AnomalyObjects[0].push_back(spider);
	}
	GameObject* spiderBig = new Spider2;
	_AnomalyObjects[0].push_back(spiderBig); // 6
	GameObject* snake = new Snake;
	_AnomalyObjects[0].push_back(snake);     // 7

	//=============
	//	2구역 : scarecrow
	//=============
	for (int i = 0; i < 4; i++) {
		GameObject* scareCrow = new ScareCrow;
		_AnomalyObjects[1].push_back(scareCrow);
	}
	GameObject* scareCrow_Anomaly = new ScareCrow;
	scareCrow_Anomaly->SetMoveAnomalyState(true);
	_AnomalyObjects[1].push_back(scareCrow_Anomaly);

	//=============
	//	3구역 : sunflower
	//=============
	for (int i = 0; i < 5; i++) {
		GameObject* sunFlower = new SunFlower;
		_AnomalyObjects[2].push_back(sunFlower);
	}
	GameObject* sunFlower_Anomaly = new SunFlower_Anomaly;
	_AnomalyObjects[2].push_back(sunFlower_Anomaly);

	//=============
	//	4구역 : horsecar
	//=============

	//=============
	//	5구역 : spider_hive
	//=============

	//=============
	//	6구역 : woodhouse
	//=============

	GameObject* bg = new BackGround;
	bg->SetLocation(Vector3(-(float)(WindowWidth / 2), -(float)(WindowHeight / 2), 0));
	AddObject(bg, LAYER_GROUP::BACKGROUND);

	GameObject* npc = new NPC;
	npc->SetEnable(true);
	AddObject(npc, LAYER_GROUP::TRAPTRIGGER);

	

	GameObject* player = new Player;
	player->SetLocation(Vector3(-800, 230, 0));
	AddObject(player, LAYER_GROUP::PLAYER);
	
	camera->SetTarget(player);

	InitObjectPlace();
}

void TrapSceneTest::End() 
{
	ResetObjectPos();
	SceneEnd();
}

void TrapSceneTest::InitObjectPlace()
{
	for (int i = 0; i < _AnomalyObjects.size(); i++) {
		for (int j = 0; j < _AnomalyObjects[i].size(); j++) {
			_AnomalyObjects[i][j]->SetLocation(Vector3(-10000.0f, -10000.0f, 0));
			_AnomalyObjects[i][j]->SetEnable(false);
		}
	}

	Vector3 areaOffset(-(float)(WindowWidth / 2), -(float)(WindowHeight / 2), 0.0f);
	int diffCount = _StageSet[_StageNum].first;
	int moveCount = _StageSet[_StageNum].second;

	// state = 0 -> Normal / state = 1 -> diffimage / state = 2 -> moveobject
	memset(_AreaSettingState, 0, sizeof(_AreaSettingState));
	SetDiffAnomaly(diffCount);
	SetMoveAnomaly(moveCount);

	for (int areaIdx = 1; areaIdx < 2; areaIdx++) {
		Vector3 worldLocation(areaOffset._x + _AreaWidth * 0, areaOffset._y, areaOffset._z);
		int targetObject;
		if (_AreaSettingState[areaIdx] == 1) {
			targetObject = GetRandomNum(_AreaObjectCount[areaIdx]);
			for (int i = 0; i < _AreaObjectCount[areaIdx]; i++) {
				_AnomalyObjects[areaIdx][i]->SetLocation(resourceManager->GetMapPos(L"area" + std::to_wstring(areaIdx + 1))[i] + worldLocation);
				_AnomalyObjects[areaIdx][i]->SetEnable(true);
				if (i == targetObject) {
					_AnomalyObjects[areaIdx][i]->SetDiffAnomalyState(true);
				}
				AddObject(_AnomalyObjects[areaIdx][i], LAYER_GROUP::MONSTER);
			}
		}
		else if (_AreaSettingState[areaIdx] == 2) {
			targetObject = GetRandomNum(_AreaObjectCount[areaIdx]);
			for (int i = 0; i < _AreaObjectCount[areaIdx]; i++) {
				if (i == targetObject) {
					int moveIdx = GetRandomNum(_AreaMoveAnomalyCount[areaIdx]);
					_AnomalyObjects[areaIdx][_AreaObjectCount[areaIdx] + moveIdx]
						->SetLocation(resourceManager->GetMapPos(L"area" + std::to_wstring(areaIdx + 1))[i] + worldLocation);
					_AnomalyObjects[areaIdx][_AreaObjectCount[areaIdx] + moveIdx]->SetEnable(true);
					AddObject(_AnomalyObjects[areaIdx][_AreaObjectCount[areaIdx] + moveIdx], LAYER_GROUP::MONSTER);
					continue;
				}
				_AnomalyObjects[areaIdx][i]->SetLocation(resourceManager->GetMapPos(L"area" + std::to_wstring(areaIdx + 1))[i] + worldLocation);
				_AnomalyObjects[areaIdx][i]->SetEnable(true);
				AddObject(_AnomalyObjects[areaIdx][i], LAYER_GROUP::MONSTER);
			}
		}
		else {
			for (int i = 0; i < _AreaObjectCount[areaIdx]; i++) {
				_AnomalyObjects[areaIdx][i]->SetLocation(resourceManager->GetMapPos(L"area" + std::to_wstring(areaIdx + 1))[i] + worldLocation);
				_AnomalyObjects[areaIdx][i]->SetEnable(true);
				AddObject(_AnomalyObjects[areaIdx][i], LAYER_GROUP::MONSTER);
			}
		}
	}
}

void TrapSceneTest::SetDiffAnomaly(int count)
{
	if (count == 0) return;
	while (count > 0) {
		int randomNum = GetRandomNum(_AreaCount);
		if (randomNum == 5 && _StageNum == 6) continue;
		if (_AreaSettingState[randomNum] == 0) {
			_AreaSettingState[randomNum] = 1;
			count--;
		}
	}
}

void TrapSceneTest::SetMoveAnomaly(int count)
{
	if (count == 0) return;
	while (count > 0) {
		int randomNum = GetRandomNum(_AreaCount);
		if (randomNum == 5 && _StageNum != 6) continue;
		if (_AreaSettingState[randomNum] == 0 && _AreaMoveAnomalyCount[randomNum] != 0) {
			_AreaSettingState[randomNum] = 2;
			count--;
		}
	}
}

void TrapSceneTest::ResetObjectPos()
{
	for (int i = 0; i < _AnomalyObjects.size(); i++) {
		for (int j = 0; j < _AnomalyObjects[i].size(); j++) {
			_AnomalyObjects[i][j]->SetLocation(Vector3(-10000.0f, -10000.0f, 0));
			_AnomalyObjects[i][j]->SetEnable(false);
			_AnomalyObjects[i][j]->ResetState();
		}
	}
}
