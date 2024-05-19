#include "Utility.h"
#include "EventManager.h"
#include "SceneManager.h"

void CreateObject(GameObject* obj, LAYER_GROUP group)
{
	Event tEvent = {};
	tEvent.Event = EVENT_TYPE::CREATE_OBJECT;
	tEvent.lParam = (DWORD_PTR)obj;
	tEvent.wParam = (DWORD_PTR)group;

	eventManager->AddEvent(tEvent);
}

void DeleteObject(GameObject* obj)
{
	Event tEvent = {};
	tEvent.Event = EVENT_TYPE::DELETE_OBJECT;
	tEvent.lParam = (DWORD_PTR)obj;

	eventManager->AddEvent(tEvent);
}

bool CheckRenderPosition(int& leftX, int& leftY, int& rightX, int& rightY)
{
	if (rightX < 0 || leftX > WindowWidth || rightY < 0 || leftY > WindowHeight) {
		return false;
	}
	return true;
}

void SceneReload()
{
	sceneManager->SceneReload();
}

int GetRandomNum(int dis)
{
	std::random_device rd;
	std::mt19937_64 mt(rd());
	std::uniform_int_distribution<int> dist(0, dis - 1);
	return dist(mt);
}
