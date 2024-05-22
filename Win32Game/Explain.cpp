#include "Explain.h"

Explain::Explain(): _MyTex(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"Explain", L"Image\\SunFlower_Anomaly.png");
	SetLocation(Vector3(500, 500, 0));
}



Explain::~Explain()
{
}

void Explain::Init(int stage)
{
	if (stage != 1)
	{
		SetEnable(false);
	}
}

void Explain::Update()
{
}

void Explain::Render()
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
}
