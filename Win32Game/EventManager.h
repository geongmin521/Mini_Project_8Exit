#pragma once
#include "globalheader.h"

#define eventManager EventManager::GetInstance()

struct Event {
	EVENT_TYPE Event;
	DWORD_PTR lParam;
	DWORD_PTR wParam;
};

class EventManager
{
public:
	EventManager();
	~EventManager();

	static EventManager* GetInstance();
	static void DestroyInstance();

	void Update();

	void AddEvent(const Event& e) { _Events.push(e); }

private:
	static EventManager* Instance;

	std::queue<Event> _Events;
	std::vector<GameObject*> _DeadObjects;

	void Excute(const Event& e);
};

