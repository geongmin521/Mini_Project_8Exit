#include "SampleObject.h"
#include "ResourceManager.h"
#include "InputSystem.h"
#include "RenderSystem.h"
#include "TimeSystem.h"
#include "Collider.h"

SampleObject::SampleObject() : _MyTex(nullptr)
{
	_MyTex = ResourceManager::GetInstance()->GetTexture(L"Charactor", L"CharactorTest.bmp");
	GameObject::CreateCollider();
	GetCollider()->SetScale(Vector3((float)_MyTex->Width(), (float)_MyTex->Height(), 0));
	GetCollider()->SetOffset(Vector3((float)_MyTex->Width() / 2, (float)_MyTex->Height() / 2, 0));
}

SampleObject::~SampleObject()
{
}

void SampleObject::Update()
{
	Vector3 dir(0, 0, 0);
	if (InputSystem::GetInstance()->isKey(VK_UP)) {
		dir += Vector3(0, -1, 0);
	}
	if (InputSystem::GetInstance()->isKey(VK_DOWN)) {
		dir += Vector3(0, 1, 0);
	}
	if (InputSystem::GetInstance()->isKey(VK_LEFT)) {
		dir += Vector3(-1, 0, 0);
	}
	if (InputSystem::GetInstance()->isKey(VK_RIGHT)) {
		dir += Vector3(1, 0, 0);
	}
	
	SetLocation(GetLocation() + dir * _MoveSpeed * TimeManager::GetInstance()->GetDeltaTime());
}

void SampleObject::Render()
{
	BitBlt(RenderSystem::GetInstance()->_backDC,
		(int)GameObject::GetLocation()._x, 
		(int)GameObject::GetLocation()._y,
		(int)_MyTex->Width(), (int)_MyTex->Height(), _MyTex->GetDC(), 0, 0, SRCCOPY);
	ComponentRender();
}
