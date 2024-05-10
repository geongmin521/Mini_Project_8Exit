#include "EventManager.h"
#include "SceneManager.h"

EventManager* EventManager::Instance = nullptr;

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
}

EventManager* EventManager::GetInstance()
{
	if (Instance == nullptr) {
		Instance = new EventManager;
	}
	return Instance;
}

void EventManager::DestroyInstance()
{
	delete Instance;
	Instance = nullptr;
}

void EventManager::Update()
{
	for (int i = 0; i < _DeadObjects.size(); i++) {
		delete _DeadObjects[i];
	}
	_DeadObjects.clear();

	while (!_Events.empty()) {
		Excute(_Events.front());
		_Events.pop();
	}
}

void EventManager::Excute(const Event& e)
{
	// lParam : obj ptr
	// wParam : obj group
	switch (e.Event) {
	case EVENT_TYPE::CREATE_OBJECT:
	{
		GameObject* newObj = (GameObject*)e.lParam;
		LAYER_GROUP group = (LAYER_GROUP)e.wParam;
		SceneManager::GetInstance()->GetCurScene()->AddObject(newObj, group);
	}
		break;
	case EVENT_TYPE::DELETE_OBJECT:
		//삭제 예정인 오브젝트들을 모아둬야 합니다.
	{
		GameObject* delObj = (GameObject*)e.lParam;
		delObj->SetDead();
		_DeadObjects.push_back(delObj);
	}

		break;
	case EVENT_TYPE::SCENE_CHANGE:

		break;
	default:
		break;
	}
}
