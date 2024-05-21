#include "WoodSign.h"

WoodSign::WoodSign() : _MyTex(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"WoodSign", L"Image\\Sign.png");
	GameObject::CreateText(30, Color(255, 255, 255, 255), (int)FontType::dialog);
	GetTextComponent()->SetRect(Vector3((float)_MyTex->Width(), (float)_MyTex->Height(), 0));
	Init(1);
}

WoodSign::~WoodSign()
{
}

void WoodSign::Init(int _SceneNum)
{
	GetTextComponent()->SetText(std::to_wstring(_SceneNum));
}

void WoodSign::Update()
{
}

void WoodSign::Render()
{
	Vector3 renderPosition = camera->GetRenderPos(GameObject::GetLocation());
	Graphics g(renderSystem->_backDC);

	int startX = (int)renderPosition._x - (int)_MyTex->Width() / 2;
	int startY = (int)renderPosition._y - (int)_MyTex->Height() / 2;
	int endX = (int)_MyTex->Width();
	int endY = (int)_MyTex->Height();

	if (CheckRenderPosition(startX, startY, endX, endY) == true) {
		g.DrawImage(_MyTex->GetImage(),
			startX, startY,
			endX, endY
		);
	}
	if (GetTextComponent() != nullptr)
	{
		GetTextComponent()->Render();
	}
}
