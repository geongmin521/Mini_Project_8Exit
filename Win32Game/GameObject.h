#pragma once
#include "Vector3.h"
#include "TimeSystem.h"
#include "InputSystem.h"
#include "globalheader.h"
#include "Camera.h"
#include "Animation.h"

class Collider;
class Animation;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	void SetLocation(const Vector3& loc) { _Location = loc; }
	void SetScale(const Vector3& scale) { _Scale = scale; }
	void Setname(const std::wstring& name) { _Name = name; }
	void SetEnable(bool state) { _Enable = state; }
	void CreateCollider();
	void CreateAnimater(std::wstring name);
	Vector3 GetLocation() const { return Vector3(_Location); }
	Vector3 GetScale() const { return Vector3(_Scale); }
	const std::wstring& GetName() const { return _Name; }
	bool Enable() { return _Enable; }

	bool IsAlive() { return _Alive; }

	virtual void FinalUpdate() final;
	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual void OnCollisionEnter(Collider* collider) {}
	virtual void OnCollision(Collider* collider) {}
	virtual void OnCollisionExit(Collider* collider) {}

	void ComponentRender();
	Collider* GetCollider() { return _Collider; }
	Animation* GetAinmater() { return _Animater; }

private:
	Vector3 _Location;
	Vector3 _Scale;
	std::wstring _Name;
	bool _Enable = true;

	bool _Alive = true;

	Collider* _Collider;
	Animation* _Animater;

	void SetDead() { _Alive = false; }

	friend class EventManager;
};

/*
	게임오브젝트가 공통적으로 가지고 있는 특성 : 
	스프라이트 ID, 위치

*/