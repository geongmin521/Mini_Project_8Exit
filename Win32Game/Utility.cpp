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
	Vector3 mousePos(inputSystem->GetMouseState()._x, inputSystem->GetMouseState()._y, 0);
	return mousePos;
}

Vector3 GetWorldMousePos()
{
	Vector3 mousePos(inputSystem->GetMouseState()._x, inputSystem->GetMouseState()._y, 0);
	Vector3 worldPos = camera->GetRenderPos(mousePos);
	return worldPos;
}

bool CheckPositionOnUI()
{
	Vector3 mousePos = GetMousePos();
	std::vector<GameObject*> uiObjects = sceneManager->GetCurScene()->GetGroupObject(LAYER_GROUP::UI);
	for (int i = 0; i < uiObjects.size(); i++) {
		if (uiObjects[i]->Enable() == true) {
			Vector3 uiObjPos = uiObjects[i]->GetLocation();
			Vector3 uiObjScale = uiObjects[i]->GetScale();
			if (
				uiObjPos._x - uiObjScale._x >= mousePos._x &&
				uiObjPos._x + uiObjScale._x <= mousePos._x &&
				uiObjPos._y - uiObjScale._y >= mousePos._y &&
				uiObjPos._y + uiObjScale._y <= mousePos._y) {
				return true;
			}
		}
	}
	return false;
}

bool CheckPositionOnUI(GameObject* obj)
{
	Vector3 mousePos = GetMousePos();
	if (obj->Enable() == true) {
		Vector3 uiObjPos = obj->GetLocation();
		Vector3 uiObjScale = obj->GetScale();
		if (
			uiObjPos._x - uiObjScale._x / 2.0f <= mousePos._x &&
			uiObjPos._x + uiObjScale._x / 2.0f >= mousePos._x &&
			uiObjPos._y - uiObjScale._y / 2.0f <= mousePos._y &&
			uiObjPos._y + uiObjScale._y / 2.0f >= mousePos._y) {
			return true;
		}
	}
	return false;
}

GameObject* GetUIObject(const std::wstring& name)
{
	std::vector<GameObject*> uiObjects = sceneManager->GetCurScene()->GetGroupObject(LAYER_GROUP::UI);
	for (int i = 0; i < uiObjects.size(); i++) {
		if (uiObjects[i]->GetName() == name) {
			return uiObjects[i];
		}
	}
	// TODO: 여기에 return 문을 삽입합니다.
}
