#pragma once
#include "GameObject.h"
#include "Texture.h"

class Player : public GameObject
{
public:
	Player();
	~Player();
	void Update();
	void Render();
	void Move();
	void Jump();

	float GetSpeed() { return _Speed; }

private:
	Texture* _MyTex;
	float _Speed;
	float _JumpPower;
	bool _IsJump;
	bool _IsHit;

};

