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
	float _Stamina;         // ���� ���¹̳�
	float _MaxStamina;      // �ִ� ���¹̳�
	float _StaminaDrain;    // �޸��� �� �ʴ� ���¹̳� �Ҹ�
	float _StaminaRecovery; // �ʴ� ���¹̳� ȸ����
	bool _IsJump;
	bool _IsHit;
	bool _IsRun;

	StaminaBar* _StaminaBar;
	StaminaBarMin* _StaminaBarMin;
};

