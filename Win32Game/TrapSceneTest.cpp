#include "TrapSceneTest.h"
#include "Camera.h"
#include "CollisionManager.h"
#include "InGameObjectHeader.h"

TrapSceneTest::TrapSceneTest() : _PrevTrapIdx(-1), _AnomalyObjects(6), _AreaWidth(3840), _StageNum(1), _AreaSettingState{}
{
	//TODO: 여기서 각 구역 별 오브젝트를 생성해야 합니다.
	
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
	for (int i = 0; i < 5; i++) {
		GameObject* spider = new Spider1;
		dynamic_cast<Spider1*>(spider)->SetStopLoc(100.0f);
		_AnomalyObjects[0].push_back(spider);
	}
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
	GameObject* merchant = new Merchant();
	_AnomalyObjects[3].push_back(merchant);
	GameObject* horse = new Horse();
	_AnomalyObjects[3].push_back(horse);
	GameObject* horseCar = new HorseCar();
	_AnomalyObjects[3].push_back(horseCar);

	//=============
	//	5구역 : spider_hive
	//=============
	for (int i = 0; i < 5; i++) {
		GameObject* spider = new Spider1;
		_AnomalyObjects[4].push_back(spider);
	}
	GameObject* scareCrow_Rotate = new ScareCrow_Rotate;
	_AnomalyObjects[4].push_back(scareCrow_Rotate);

	GameObject* scareCrowRotate_Anomaly = new ScareCrow_Rotate;
	scareCrowRotate_Anomaly->SetMoveAnomalyState(true);
	_AnomalyObjects[4].push_back(scareCrowRotate_Anomaly);

	//=============
	//	6구역 : woodhouse
	//=============
	for (int i = 0; i < 1; i++) {
		GameObject* woodhouse = new WoodHouse;
		_AnomalyObjects[5].push_back(woodhouse);
	}
	GameObject* woodhouse2 = new WoodHouse2;
	_AnomalyObjects[5].push_back(woodhouse2);





	MainGameUI* mainUi = new MainGameUI;
	AddObject(mainUi, LAYER_GROUP::UI);

	PauseUI* pauseUi = new PauseUI;
	pauseUi->SetEnable(false);
	AddObject(pauseUi, LAYER_GROUP::UI);

	GameObject* bg = new GameBG;
	bg->SetLocation(Vector3(-(float)(WindowWidth / 2), -(float)(WindowHeight / 2), 0));
	AddObject(bg, LAYER_GROUP::BACKGROUND);
	GameObject* bg2 = new GameBG;
	bg2->SetLocation(Vector3(-(float)(WindowWidth / 2) + 11520.0f, -(float)(WindowHeight / 2), 0));
	AddObject(bg2, LAYER_GROUP::BACKGROUND);

	GameObject* sign = new WoodSign;
	sign->SetLocation(Vector3(-250.0f, 220.0f, 0));
	AddObject(sign, LAYER_GROUP::BACKUNIT);

	GameObject* npc = new NPC;
	npc->SetLocation(Vector3(-250.0f, 80, 0));
	AddObject(npc, LAYER_GROUP::SEARCH);

	GameObject* player = new Player;
	player->SetLocation(Vector3(-800, 230, 0));
	AddObject(player, LAYER_GROUP::PLAYER);
	
	timeManager->SetTimeScale(1.0f);

	camera->SetTarget(player);

	for (int i = 0; i < _AnomalyObjects.size(); i++) {
		for (int j = 0; j < _AnomalyObjects[i].size(); j++) {
			AddObject(_AnomalyObjects[i][j], LAYER_GROUP::MONSTER);
		}
	}

	InitObjectPlace();
}

void TrapSceneTest::End() 
{
	SceneEnd();
}

void TrapSceneTest::InitObjectPlace()
{
	

	GetGroupObject(LAYER_GROUP::PLAYER)[0]->SetLocation(Vector3(-800, 230, 0));
	for (int i = 0; i < _AnomalyObjects.size(); i++) {
		for (int j = 0; j < _AnomalyObjects[i].size(); j++) {
			_AnomalyObjects[i][j]->SetLocation(Vector3(-10000.0f, -10000.0f, 0));
			//_AnomalyObjects[i][j]->SetEnable(false);
		}
	}

	Vector3 areaOffset(-(float)(WindowWidth / 2), -(float)(WindowHeight / 2), 0.0f);
	int diffCount = _StageSet[_StageNum].first;
	int moveCount = _StageSet[_StageNum].second;

	// state = 0 -> Normal / state = 1 -> diffimage / state = 2 -> moveobject
	memset(_AreaSettingState, 0, sizeof(_AreaSettingState));
	SetDiffAnomaly(diffCount);
	SetMoveAnomaly(moveCount);

	

	for (int areaIdx = 0; areaIdx < 6; areaIdx++) {
		Vector3 worldLocation(areaOffset._x + _AreaWidth * areaIdx, areaOffset._y, areaOffset._z);
		int targetObject;
		std::vector<Vector3> pos = resourceManager->GetMapPos(L"area" + std::to_wstring(areaIdx + 1));
		if (_AreaSettingState[areaIdx] == 1) {
			targetObject = GetRandomNum(_AreaObjectCount[areaIdx]);
			_AnomalyIdx.push_back({ areaIdx, targetObject });
			for (int i = 0; i < _AreaObjectCount[areaIdx]; i++) {//GetMapPos 로 백터를 통해 사이즈 구하기 즉 오브젝트 카운트 제거
				_AnomalyObjects[areaIdx][i]->SetLocation(resourceManager->GetMapPos(L"area" + std::to_wstring(areaIdx + 1))[i] + worldLocation);
				_AnomalyObjects[areaIdx][i]->SetEnable(true);
				if (i == targetObject) {
					_AnomalyObjects[areaIdx][i]->SetDiffAnomalyState(true);
				}
				
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
			}
		}
		else {
			for (int i = 0; i < _AreaObjectCount[areaIdx]; i++) {
				_AnomalyObjects[areaIdx][i]->SetLocation(resourceManager->GetMapPos(L"area" + std::to_wstring(areaIdx + 1))[i] + worldLocation);
				_AnomalyObjects[areaIdx][i]->SetEnable(true);
			}
		}
	}
}

void TrapSceneTest::NextStage()
{
	if (CheckCorrect() == true) {
		_StageNum++;
	}
	else {
		if (_StageNum > 1) {
			_StageNum--;
		}
	}
	ResetObjectPos();
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
			//_AnomalyObjects[i][j]->SetEnable(false);
			_AnomalyObjects[i][j]->ResetState();
		}
	}
}

bool TrapSceneTest::CheckCorrect() {
	std::vector<GameObject*> checkedObj = dynamic_cast<Player*>(GetGroupObject(LAYER_GROUP::PLAYER)[0])->GetCheckObject();
	std::set<std::pair<int, int>> objIdx;
	for (int i = 0; i < checkedObj.size(); i++) {
		Vector3 checkCollisionLoc = checkedObj[i]->GetCollider()->GetPos();
		Vector3 checkCollisionScale = checkedObj[i]->GetCollider()->GetScale();
		for (int j = 0; j < _AnomalyIdx.size(); j++) {
			Vector3 checkObjLoc = _AnomalyObjects[_AnomalyIdx[j].first][_AnomalyIdx[j].second]->GetCollider()->GetPos();
			Vector3 checkObjScale = _AnomalyObjects[_AnomalyIdx[j].first][_AnomalyIdx[j].second]->GetCollider()->GetScale();
			if (BorderCheck(checkCollisionLoc, checkCollisionScale, checkObjLoc, checkObjScale) == true) {
				objIdx.insert(_AnomalyIdx[j]);
			}
		}
	}
	if (objIdx.size() == _AnomalyIdx.size()) {
		return true;
	}
	else {
		return false;
	}
}
