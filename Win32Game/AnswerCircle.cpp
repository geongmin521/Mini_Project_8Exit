#include "AnswerCircle.h"
#include "Collider.h"
AnswerCircle::AnswerCircle()
{
	_MyTex = resourceManager->GetTexture(L"Answer", L"Image\\UI\\Circle.png");
	SetScale(Vector3((float)_MyTex->Width(), (float)_MyTex->Height(), 0));
	SetEnable(false);
	CreateCollider();
	GetCollider()->SetScale(GetScale());
}

AnswerCircle::~AnswerCircle()
{
}

void AnswerCircle::Update()
{
}

void AnswerCircle::Render()
{
	Vector3 renderPosition = camera->GetRenderPos(GameObject::GetLocation());
	Gdiplus::Graphics g(renderSystem->_backDC);
	g.DrawImage(_MyTex->GetImage(),
		(int)renderPosition._x - (int)_MyTex->GetImage()->GetWidth() / 2,
		(int)renderPosition._y - (int)_MyTex->GetImage()->GetHeight() / 2,
		(int)_MyTex->GetImage()->GetWidth(), (int)_MyTex->GetImage()->GetHeight()
	);
}
