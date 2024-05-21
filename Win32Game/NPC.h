#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "TextBox.h"

enum class NPCState
{
	Idle,
	Talk
};

class NPC : public GameObject //�ؽ�Ʈ ������Ʈ�� ���� ������Ʈ
{
public:
	NPC();
	~NPC();
	void Update();
	void Render();
	void OnTriggerEnter(Collider* collider);
	void OnTriggerExit(Collider* collider);
private:
	NPCState _State;
	TextBox* _TextBox;
	Texture* _MyTex;
	//�ؽ�Ʈ �޾ƿ��¾˰���
};

