#pragma once
#include "globalheader.h"
#define IGNORE_UTILITY

class GameObject;

void CreateObject(GameObject* obj, LAYER_GROUP group);
void DeleteObject(GameObject* obj);
