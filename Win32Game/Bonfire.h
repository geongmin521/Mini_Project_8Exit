#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "TextBox.h"
enum class BONFIRE_STATE {
	IDLE
};
class Bonfire : public GameObject //텍스트 컴포넌트를 가질 오브젝트
{
public:
	Bonfire();
	~Bonfire();
	void Update();
	void Render();
	void ResetState();
	void StateChange(BONFIRE_STATE bonfireState);
	void OnTriggerExit(Collider* collision);
	void OnTriggerEnter(Collider* collision);
private:
	BONFIRE_STATE _BonfireState;
	TextBox* _TextBox;
	Texture* _MyTex;
};

