#include "House.h"
#include "Collider.h"
#include "SceneManager.h"

House::House() : _MyTex(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"House", L"Image\\Cottage_Player.png");
	CreateCollider();
	GetCollider()->SetScale(Vector3(300.0f, 425.0f, 0));
	GetCollider()->SetOffset(Vector3(0, 210.0f, 0));
	GetCollider()->SetTrigger(true);
}

House::~House()
{
}

void House::Update()
{
}

void House::Render()
{
	Vector3 renderPosition = camera->GetRenderPos(GameObject::GetLocation());
	Graphics g(renderSystem->_backDC);

	int startX = (int)renderPosition._x - (int)_MyTex->Width() / 2;
	int startY = (int)renderPosition._y - (int)_MyTex->Height() / 2;
	int endX = (int)_MyTex->Width();
	int endY = (int)_MyTex->Height();

	g.DrawImage(_MyTex->GetImage(),
		startX, startY,
		endX, endY
	);

	ComponentRender();
}

void House::OnTriggerEnter(Collider* collider)
{
	sceneManager->LoadScene(SCENE_LAYER::ENDINGSTORY);
}
