#include "Button_Title.h"
#include "ResourceManager.h"

Button_Title::Button_Title() : _MyTex(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"Button_Title", L"Image\\Button\\Button_Title.png");
}

Button_Title::~Button_Title()
{
}

void Button_Title::Update()
{

}

void Button_Title::Render()
{
	Graphics g(renderSystem->_backDC);
	int endX = (int)_MyTex->Width();
	int endY = (int)_MyTex->Height();

	g.DrawImage(_MyTex->GetImage(),
		(INT)_Pos._x - endX / 2, (INT)_Pos._y - endY / 2,
		endX, endY
	);
}
