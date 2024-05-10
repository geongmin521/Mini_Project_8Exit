#include "Utility.h"
#include "EventManager.h"

void CreateObject(GameObject* obj, LAYER_GROUP group)
{
	Event tEvent = {};
	tEvent.Event = EVENT_TYPE::CREATE_OBJECT;
	tEvent.lParam = (DWORD_PTR)obj;
	tEvent.wParam = (DWORD_PTR)group;

	EventManager::GetInstance()->AddEvent(tEvent);
}

void DeleteObject(GameObject* obj)
{
	Event tEvent = {};
	tEvent.Event = EVENT_TYPE::DELETE_OBJECT;
	tEvent.lParam = (DWORD_PTR)obj;

	EventManager::GetInstance()->AddEvent(tEvent);
}
