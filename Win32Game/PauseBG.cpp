#include "PauseBG.h"
#include "ResourceManager.h"

PauseBG::PauseBG() : _MyTex(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"PauseBG", L"Image\\Screen_Pause.png");
}

PauseBG::~PauseBG()
{
}

void PauseBG::Update()
{

}

void PauseBG::Render()
{
	Graphics g(renderSystem->_backDC);
	int endX = (int)_MyTex->Width();
	int endY = (int)_MyTex->Height();

	g.DrawImage(_MyTex->GetImage(),
		0, 0,
		endX, endY
	);
}
