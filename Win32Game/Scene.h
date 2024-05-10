#pragma once
#include "globalheader.h"
#include "GameObject.h"

class Scene {
public:
	Scene();
	virtual ~Scene();

	void SetSceneName(std::string& name) { _SceneName = name; }
	std::string GetSceneName() const { return _SceneName; }

	virtual void Start() = 0;
	virtual void End() = 0;

	void Update();
	void FinalUpdate();
	void Render();
	void SceneEnd();

	const std::vector<GameObject*>& GetGroupObject(LAYER_GROUP group) const { return _GameObjects[(int)group]; }

public:
	void AddObject(GameObject* obj, LAYER_GROUP layer) { _GameObjects[(int)layer].push_back(obj); }

private:
	std::vector<GameObject*> _GameObjects[(int)LAYER_GROUP::END];
	std::string _SceneName;
};