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

Vector3 GetMousePos()
{
	return Vector3(inputSystem->GetMouseState()._x, inputSystem->GetMouseState()._y, 0);
}

bool CheckPositionOnUI(Vector3& pos)
{
	std::vector<GameObject*> uiObjects = sceneManager->GetCurScene()->GetGroupObject(LAYER_GROUP::UI);
	for (int i = 0; i < uiObjects.size(); i++) {
		if (uiObjects[i]->Enable() == true) {
			Vector3 uiObjPos = uiObjects[i]->GetLocation();
			Vector3 uiObjScale = uiObjects[i]->GetScale();
			if (
				uiObjPos._x - uiObjScale._x >= pos._x &&
				uiObjPos._x + uiObjScale._x <= pos._x &&
				uiObjPos._y - uiObjScale._y >= pos._y &&
				uiObjPos._y - uiObjScale._y <= pos._y) {
				return true;
			}
		}
	}
	return false;
}
