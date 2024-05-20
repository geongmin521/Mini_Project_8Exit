#pragma once
#include "Vector3.h"
#include "TimeSystem.h"
#include "InputSystem.h"
#include "globalheader.h"
#include "Camera.h"
#include "Animation.h"
#include "Text.h"
class Collider;
class Animation;
class Text;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	void SetLocation(const Vector3& loc) { _Location = loc; }
	void SetScale(const Vector3& scale) { _Scale = scale; }
	void SetName(const std::wstring& name) { _Name = name; }
	void SetEnable(bool state) { _Enable = state; }
	void SetDir(Vector3& dir) { _Dir = dir; }
	void SetDiffAnomalyState(bool state) { _IsDiffAnomaly = state; }
	void SetMoveAnomalyState(bool state) { _IsMoveAnomaly = state; }
	void SetFlipX(bool flipX) { _FlipX = flipX; }
	void CreateCollider();
	void CreateText();
	void CreateAnimater(std::wstring name, float animationTime);
	Vector3 GetLocation() const { return Vector3(_Location); }
	Vector3 GetScale() const { return Vector3(_Scale); }
	bool GetFlipX() const { return _FlipX; }
	Vector3 GetDir() const { return _Dir; }
	const std::wstring& GetName() const { return _Name; }
	bool Enable() { return _Enable; }
	const bool GetDiffAnomalyState() const { return _IsDiffAnomaly; }
	const bool GetMoveAnomalyState() const { return _IsMoveAnomaly; }
	bool IsAlive() { return _Alive; }

	virtual void FinalUpdate() final;
	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual void ResetState() {}

	virtual void OnCollisionEnter(Collider* collider) {}
	virtual void OnCollision(Collider* collider) {}
	virtual void OnCollisionExit(Collider* collider) {}

	virtual void OnTriggerEnter(Collider* collider) {}
	virtual void OnTrigger(Collider* collider) {}
	virtual void OnTriggerExit(Collider* collider) {}

	void ComponentRender();
	Collider* GetCollider() { return _Collider; }
	Animation* GetAinmater() { return _Animater; }
	Text* GetTextComponent() { return _Text; }

private:
	Vector3 _Location;
	Vector3 _Scale;
	Vector3 _Dir;
	bool _FlipX;
	std::wstring _Name;
	bool _Enable = true;
	bool _IsDiffAnomaly = false;
	bool _IsMoveAnomaly = false;
	bool _Alive = true;

	Collider* _Collider;
	Animation* _Animater;
	Text* _Text;
	void SetDead() { _Alive = false; }

	friend class EventManager;
};

/*
	게임오브젝트가 공통적으로 가지고 있는 특성 : 
	스프라이트 ID, 위치

*/