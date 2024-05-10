#pragma once
#include "Vector3.h"
#include "GameObject.h"

class GameObjcet;

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

	// 기본 대입 연산자가 작동하지 않게 미리 방어를 해줍니다.
	Collider& operator= (Collider& origin) = delete;
private:
	GameObject* _Owner;
	Vector3 _Offset;
	Vector3 _ColliderPos;
	Vector3 _Scale;

	// Collider가 생성될 때 마다 고유한 번호를 가지게 하기 위해서 정적변수를 선언합니다.
	static UINT _NextID;
	UINT _ID;

	friend class GameObject;
};

