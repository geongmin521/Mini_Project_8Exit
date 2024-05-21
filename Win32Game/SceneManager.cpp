#include "SceneManager.h"
#include "SampleScene.h"
#include "TrapSceneTest.h"
#include "Scene.h"
#include "LobbyScene.h"
#include "OpeningScene.h"
#include "HomeScene.h"

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
	_Scenes[(int)SCENE_LAYER::MAIN] = new LobbyScene;
	_Scenes[(int)SCENE_LAYER::STORY] = new OpeningScene;
	_Scenes[(int)SCENE_LAYER::PLAY] = new TrapSceneTest;
	_Scenes[(int)SCENE_LAYER::ENDING] = new HomeScene;
	_CurScene = _Scenes[(int)SCENE_LAYER::PLAY];
	_CurScene->Start();
}

void SceneManager::Update() {
	_CurScene->Update();
	_CurScene->FinalUpdate();
}

void SceneManager::Render() {
	_CurScene->Render();
}

void SceneManager::LoadScene(SCENE_LAYER layer)
{
	_CurScene->End();
	_CurScene = _Scenes[(int)layer];
	_CurScene->Start();
}

void SceneManager::SceneReload()
{
	dynamic_cast<TrapSceneTest*>(_CurScene)->NextStage();
	dynamic_cast<TrapSceneTest*>(_CurScene)->InitObjectPlace();
}
