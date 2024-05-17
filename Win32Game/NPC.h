#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "TextBox.h"
class NPC : public GameObject //텍스트 컴포넌트를 가질 오브젝트
{
public:
	NPC();
	~NPC();
	void Update();
	void Render();
	void OnCollisionEnter(Collider* collider);
	void OnCollisionExit(Collider* collider);
private:
	TextBox* _TextBox;
	Texture* _MyTex;
};

