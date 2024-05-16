#pragma once
#include "GameObject.h"
#include "Texture.h"

enum class PlayerState
{
	idle,
	jump,
	hit,
	move
};

class Player : public GameObject
{
public:
	Player();
	~Player();
	void Update();
	void Render();
	void Move();
	void Jump();
	void ChangeState(PlayerState state);

	float GetSpeed() { return _Speed; }



private:
	PlayerState _CurState;
	Texture* _MyTex;
	float _Speed;
	float _JumpPower;
	bool _IsJump;
	bool _IsHit;

};

