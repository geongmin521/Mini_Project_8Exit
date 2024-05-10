#include "Monster.h"
#include "ResourceManager.h"
#include "RenderSystem.h"
#include "Collider.h"
#include "Utility.h"

Monster::Monster() : _MyTex(nullptr)
{
	_MyTex = ResourceManager::GetInstance()->GetTexture(L"Monster", L"CharactorTest.bmp");
	CreateCollider();
	GetCollider()->SetScale(Vector3((float)_MyTex->Width(), (float)_MyTex->Height(), 0));
	GetCollider()->SetOffset(Vector3((float)_MyTex->Width() / 2, (float)_MyTex->Height() / 2, 0));
}

Monster::~Monster()
{
}

void Monster::Update()
{
}

void Monster::Render()
{
	BitBlt(RenderSystem::GetInstance()->_backDC,
		(int)GameObject::GetLocation()._x, (int)GameObject::GetLocation()._y,
		(int)_MyTex->Width(), (int)_MyTex->Height(), _MyTex->GetDC(), 0, 0, SRCCOPY);

	ComponentRender();
}

void Monster::OnCollisionEnter(Collider* collider)
{
	GameObject::SetEnable(false);
}
