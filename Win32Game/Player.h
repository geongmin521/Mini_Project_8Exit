#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "AnswerCircle.h"
#include <vector>
#include "FadeIn.h"

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
	void CheckCircle();
	void Init();
	std::vector<GameObject*>& GetCheckObject() { return _Answer; }

private:
	PlayerState _CurState;
	Texture* _MyTex;
	float _Speed;
	float _JumpPower;
	float _RunSpeed;
	float _Stamina;         // ���� ���¹̳�
	float _MaxStamina;      // �ִ� ���¹̳�
	float _StaminaDrain;    // �޸��� �� �ʴ� ���¹̳� �Ҹ�
	float _StaminaRecovery; // �ʴ� ���¹̳� ȸ����
	int Circle;// ���� ��Ŭ��?
	bool _IsJump;
	bool _IsHit;
	bool _IsRun;
	bool _IsWalk;
	bool _Runable;
	std::vector<GameObject*> _Answer;
	Texture* _AnswerUI;
	FadeIn* _FadeIn;
	StaminaBarMin* _StaminaBarMin;
};

