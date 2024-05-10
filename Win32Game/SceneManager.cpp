#include "SceneManager.h"
#include "SampleScene.h"
#include "Scene.h"

SceneManager* SceneManager::Instance = nullptr;
SceneManager::SceneManager() : _CurScene(nullptr) {
	for (int i = 0; i < (int)SCENE_LAYER::END; i++) {
		_Scenes[i] = nullptr;
	}
}
SceneManager::~SceneManager() {
	for (int i = 0; i < (int)SCENE_LAYER::END; i++) {
		if (_Scenes[i] != nullptr) {
			delete _Scenes[i];
			_Scenes[i] = nullptr;
		}
	}
}

SceneManager* SceneManager::GetInstance() {
	if(Instance == nullptr) {
		Instance = new SceneManager;
	}
	return Instance;
}

void SceneManager::DestroyInstance() {
	delete Instance;
	Instance = nullptr;
}

void SceneManager::InitScene() {
	_Scenes[(int)SCENE_LAYER::MAIN] = new SampleScene;	
	_CurScene = _Scenes[(int)SCENE_LAYER::MAIN];
	_CurScene->Start();
}

void SceneManager::Update() {
	_CurScene->Update();
	_CurScene->FinalUpdate();
}

void SceneManager::Render() {
	_CurScene->Render();
}

void SceneManager::LoadScene(int idx)
{
	_CurScene->End();
	_CurScene = _Scenes[idx];
	_CurScene->Start();
}