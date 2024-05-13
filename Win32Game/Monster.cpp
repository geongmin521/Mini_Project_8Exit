#include "Monster.h"
#include "ResourceManager.h"
#include "RenderSystem.h"
#include "Collider.h"
#include "Utility.h"

Monster::Monster() : _MyTex(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"Monster", L"Image\\alpha30.png");
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
	Vector3 renderPosition = camera->GetRenderPos(GameObject::GetLocation());

	Graphics g(renderSystem->_backDC);
	g.DrawImage(_MyTex->GetImage(),
		(int)GameObject::GetLocation()._x, (int)GameObject::GetLocation()._y,
		(int)_MyTex->GetImage()->GetWidth(), (int)_MyTex->GetImage()->GetHeight()
	);

	// BoxCollider도 캐릭터 이미지와 같이 움직이게 하려면 Update 에서 renderPosition 을 갱신해줘야 합니다.
	//ComponentRender();
}

void Monster::OnCollisionEnter(Collider* collider)
{
	GameObject::SetEnable(false);
}
