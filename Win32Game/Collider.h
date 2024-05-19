#pragma once
#include "Vector3.h"
#include "GameObject.h"

class GameObject;

class Collider
{
public:
	Collider();
	Collider(const Collider& origin);
	~Collider();

	void FinalUpdate();

	void SetOffset(const Vector3& pos) { _Offset = pos; }
	void SetPos(const Vector3& pos) { _ColliderPos = pos; }
	void SetScale(const Vector3& scale) { _Scale = scale; }
	void SetTrigger(bool state) { _Trigger = state; }

	Vector3 GetOffset() const { return _Offset; }
	Vector3 GetPos() const { return _ColliderPos; }
	Vector3 GetScale() const { return _Scale; }
	const bool IsTrigger() const { return _Trigger; }
	GameObject* GetOwnerObject() { return _Owner; }

	void Render();

	const int GetColliderID() const { return _ID; }

	void OnCollisionEnter(Collider* collider);
	void OnCollision(Collider* collider);
	void OnCollisionExit(Collider* collider);

	void OnTriggerEnter(Collider* collider);
	void OnTrigger(Collider* collider);
	void OnTriggerExit(Collider* collider);

	// �⺻ ���� �����ڰ� �۵����� �ʰ� �̸� �� ���ݴϴ�.
	Collider& operator= (Collider& origin) = delete;
private:
	GameObject* _Owner;
	Vector3 _Offset;
	Vector3 _ColliderPos;
	Vector3 _Scale;

	bool _Trigger = false;

	// Collider�� ������ �� ���� ������ ��ȣ�� ������ �ϱ� ���ؼ� ���������� �����մϴ�.
	static UINT _NextID;
	UINT _ID;

	friend class GameObject;
};

