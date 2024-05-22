#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "TextBox.h"
enum class BONFIRE_STATE {
	IDLE
};
class NPC : public GameObject //텍스트 컴포넌트를 가질 오브젝트
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

