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

	Vector3 GetOffset() const { return _Offset; }
	Vector3 GetPos() const { return _ColliderPos; }
	Vector3 GetScale() const { return _Scale; }
	GameObject* GetOwnerObject() { return _Owner; }

	void Render();

	const int GetColliderID() const { return _ID; }

	void OnCollisionEnter(Collider* collider);
	void OnCollision(Collider* collider);
	void OnCollisionExit(Collider* collider);

	// �⺻ ���� �����ڰ� �۵����� �ʰ� �̸� �� ���ݴϴ�.
	Collider& operator= (Collider& origin) = delete;
private:
	GameObject* _Owner;
	Vector3 _Offset;
	Vector3 _ColliderPos;
	Vector3 _Scale;

	// Collider�� ������ �� ���� ������ ��ȣ�� ������ �ϱ� ���ؼ� ���������� �����մϴ�.
	static UINT _NextID;
	UINT _ID;

	friend class GameObject;
};

