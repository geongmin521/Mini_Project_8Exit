#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "StaminaBar.h"
#include "StaminaBarMin.h"
class Player : public GameObject
{
public:
	Player();
	~Player();
	void Update();
	void Render();
	void Move();
	void Jump();
	void Run();
	void StaminaBarActions();
	void StaminaBarMinActions();
	
private:
	Texture* _MyTex;
	float _Speed;
	float _JumpPower;
	float _RunSpeed;
	float _BaseSpeed = _Speed;
	float _CurrentSpeed = _BaseSpeed;
	float _Stamina;         // 현재 스태미너
	float _MaxStamina;      // 최대 스태미너
	float _StaminaDrain;    // 달리기 시 초당 스태미너 소모량
	float _StaminaRecovery; // 초당 스태미너 회복량
	bool _IsJump;
	bool _IsHit;
	bool _IsRun;

	StaminaBar* _StaminaBar;
	StaminaBarMin* _StaminaBarMin;
};

