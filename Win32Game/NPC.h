#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "TextBox.h"
class NPC : public GameObject //�ؽ�Ʈ ������Ʈ�� ���� ������Ʈ
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

