#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "TextBox.h"

enum class NPCState
{
	Idle,
	Talk
};

class NPC : public GameObject //텍스트 컴포넌트를 가질 오브젝트
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
	//텍스트 받아오는알고리즘
};

