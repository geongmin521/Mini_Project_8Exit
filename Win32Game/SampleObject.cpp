#include "SampleObject.h"
#include "ResourceManager.h"
#include "InputSystem.h"
#include "RenderSystem.h"
#include "TimeSystem.h"
#include "Collider.h"

SampleObject::SampleObject() : _MyTex(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"Charactor", L"Image\\alpha100.png");
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
	if (inputSystem->isKey(VK_UP)) {
		dir += Vector3(0, -1, 0);
	}
	if (inputSystem->isKey(VK_DOWN)) {
		dir += Vector3(0, 1, 0);
	}
	if (inputSystem->isKey(VK_LEFT)) {
		dir += Vector3(-1, 0, 0);
	}
	if (inputSystem->isKey(VK_RIGHT)) {
		dir += Vector3(1, 0, 0);
	}
	
	SetLocation(GetLocation() + dir * _MoveSpeed * TimeManager::GetInstance()->GetDeltaTime());
}

void SampleObject::Render()
{
	Vector3 renderPosition = camera->GetRenderPos(GameObject::GetLocation());

	Graphics g(renderSystem->_backDC);
	g.DrawImage(_MyTex->GetImage(), 
		(int)renderPosition._x - (int)_MyTex->Width() / 2, 
		(int)renderPosition._y - (int)_MyTex->Height() / 2,
		(int)_MyTex->Width(), (int)_MyTex->Height()
	);
	//ComponentRender();
}
