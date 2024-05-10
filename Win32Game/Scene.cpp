#include "Scene.h"

Scene::Scene() {
	_SceneName = "";
}
Scene::~Scene() {
	for (int i = 0; i < (int)LAYER_GROUP::END; i++) {
		for (int j = 0; j < _GameObjects[i].size(); j++) {
			if (_GameObjects[i][j] != nullptr) {
				delete _GameObjects[i][j];
			}
		}
	}
}

void Scene::Update() {
	for (int i = 0; i < (int)LAYER_GROUP::END; i++) {
		for (int j = 0; j < _GameObjects[i].size(); j++) {
			if (_GameObjects[i][j]->IsAlive() == true) {
				if (_GameObjects[i][j]->Enable() == true) _GameObjects[i][j]->Update();
			}
		}
	}
}

void Scene::FinalUpdate()
{
	for (int i = 0; i < (int)LAYER_GROUP::END; i++) {
		for (int j = 0; j < _GameObjects[i].size(); j++) {
			if (_GameObjects[i][j]->Enable() == true) _GameObjects[i][j]->FinalUpdate();
		}
	}
}

void Scene::Render() {
	for (int i = 0; i < (int)LAYER_GROUP::END; i++) {
		std::vector<GameObject*>::iterator it = _GameObjects[i].begin();
		for (; it != _GameObjects[i].end();) {
			if ((*it)->IsAlive() == true) {
				if ((*it)->Enable() == true) (*it)->Render();
				it++;
			}
			else {
				it = _GameObjects[i].erase(it);
			}
		}
	}
}

void Scene::SceneEnd()
{
	for (int i = 0; i < (int)LAYER_GROUP::END; i++) {
		for (int j = 0; j < _GameObjects[i].size(); j++) {
			if (_GameObjects[i][j] != nullptr) {
				delete _GameObjects[i][j];
			}
		}
	}
}
