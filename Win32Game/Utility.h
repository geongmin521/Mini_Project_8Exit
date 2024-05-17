#pragma once
#include "globalheader.h"
#define IGNORE_UTILITY

class GameObject;

void CreateObject(GameObject* obj, LAYER_GROUP group);
void DeleteObject(GameObject* obj);
bool CheckRenderPosition(int& leftX, int& leftY, int& rightX, int& rightY);
void SceneReload();
