#pragma once
#include "globalheader.h"
#include "Scene.h"

#define sceneManager SceneManager::GetInstance()

class Scene;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	static SceneManager* GetInstance();
	static void DestroyInstance();
	void InitScene();
	void Update();
	void Render();
	void LoadScene(int idx);
	Scene* GetCurScene() const { return _CurScene; }

private:
	static SceneManager* Instance;
	Scene* _Scenes[(int)SCENE_LAYER::END];
	Scene* _CurScene;
};

