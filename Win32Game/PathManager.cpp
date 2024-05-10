#include "PathManager.h"

PathManager* PathManager::Instance = nullptr;

PathManager::PathManager() : _ContentPath {}
{
}

PathManager::~PathManager()
{
}

PathManager* PathManager::GetInstance()
{
	if (Instance == nullptr) {
		Instance = new PathManager;
	}
	return Instance;
}

void PathManager::DestroyInstance()
{
	delete Instance;
	Instance = nullptr;
}

void PathManager::InitPath()
{
	GetCurrentDirectory(255, _ContentPath);

	for (size_t i = wcslen(_ContentPath) - 1; i >= 0; i--) {
		if (_ContentPath[i] == '\\') {
			_ContentPath[i] = '\0';
			break;
		}
	}
	wcscat_s(_ContentPath, 255, L"\\main\\data\\image\\");
	SetWindowText(global::GetWinApp().GetWindow(), _ContentPath);
}
