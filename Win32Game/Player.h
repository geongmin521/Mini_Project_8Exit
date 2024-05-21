#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "AnswerCircle.h"
#include <vector>

enum class PlayerState
{
	Idle,
	Jump,
	Walk,
	Run,
	Hit,
};

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
	void ChangeState(PlayerState state);
	void StateManager();
	float GetSpeed() { return _Speed; }
	void Run();
	void StaminaBarActions();
	void OnCollisionEnter(Collider* collider);

	std::vector<GameObject*>& GetCheckObject() { return _Answer; }

private:
	PlayerState _CurState;
	Texture* _MyTex;
	float _Speed;
	float _JumpPower;
	float _RunSpeed;
	float _Stamina;         // 현재 스태미너
	float _MaxStamina;      // 최대 스태미너
	float _StaminaDrain;    // 달리기 시 초당 스태미너 소모량
	float _StaminaRecovery; // 초당 스태미너 회복량
	bool _IsJump;
	bool _IsHit;
	bool _IsRun;
	bool _IsWalk;
	bool _Runable;
	std::vector<GameObject*> _Answer;
	StaminaBar* _StaminaBar;
	StaminaBarMin* _StaminaBarMin;
};

