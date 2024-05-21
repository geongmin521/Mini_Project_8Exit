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
	//bool _isTalk; //�� ������Ʈ�� ���¸� ����־������������?
	//���������� npc�� ����մ°� �´µ�?
	//�ؽ�Ʈ �޾ƿ��¾˰���
};

