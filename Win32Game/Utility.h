#pragma once
#include "globalheader.h"
#define IGNORE_UTILITY

class GameObject;

void CreateObject(GameObject* obj, LAYER_GROUP group);
void DeleteObject(GameObject* obj);
bool CheckRenderPosition(int& leftX, int& leftY, int& rightX, int& rightY);
void SceneReload();
int GetRandomNum(int dis);
int GetRandomNum(int from, int to);
Vector3 GetMousePos();
Vector3 GetWorldMousePos();
bool CheckPositionOnUI();
bool CheckPositionOnUI(GameObject* obj);
GameObject* GetUIObject(const std::wstring& name);
bool BorderCheck(Vector3& aPos, Vector3& aScale, Vector3& bPos, Vector3& bScale);
GameObject* GetUIObject(const std::wstring& name); 
bool CheckPositionOnWorld(GameObject* obj);