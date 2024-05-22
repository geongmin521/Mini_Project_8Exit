#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "TextBox.h"
enum class BONFIRE_STATE {
	IDLE
};
class NPC : public GameObject //�ؽ�Ʈ ������Ʈ�� ���� ������Ʈ
{
public:
	NPC();
	~NPC();
	void Update();
	void Render();
	void ResetState();
	void OnCollisionEnter(Collider* collider);
	void OnCollisionExit(Collider* collider);
	void StateChange(BONFIRE_STATE witchState);
private:
	BONFIRE_STATE _BonfireState;
	TextBox* _TextBox;
	Texture* _MyTex;
};

