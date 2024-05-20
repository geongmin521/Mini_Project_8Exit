#include "Button_Pause.h"
#include "ResourceManager.h"

Button_Pause::Button_Pause() : _MyTex(nullptr), _Parent(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"Button_Pause", L"Image\\Button\\Button_Pause.png");
}

Button_Pause::~Button_Pause()
{
}

void Button_Pause::Update()
{
	_Pos = GetLocation() + _Parent->GetLocation();
}

void Button_Pause::Render()
{
	Graphics g(renderSystem->_backDC);
	int endX = (int)_MyTex->Width();
	int endY = (int)_MyTex->Height();

	g.DrawImage(_MyTex->GetImage(),
		(INT)_Pos._x - endX / 2, (INT)_Pos._y - endY / 2,
		endX, endY
	);
}
