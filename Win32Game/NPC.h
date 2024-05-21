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
	NPC(std::wstring DialogKey);
	~NPC();
	void Update();
	void Render();
	void OnTriggerEnter(Collider* collider);
	void OnTriggerExit(Collider* collider);
	void Init(int stage);
	void StageDioLog();
	void TutorialDiaLog();
	void EndDioLog();
private:
	NPCState _State;
	TextBox* _TextBox;
	Texture* _MyTex;
	std::wstring _DialogKey;
	int _StageNum;
	//bool _isTalk; //각 오브젝트가 상태를 들고있어야하지않을까?
	//스테이지를 npc가 들고잇는게 맞는듯?
	//텍스트 받아오는알고리즘
};

