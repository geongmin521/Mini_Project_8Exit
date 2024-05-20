#include "MainBG.h"

MainBG::MainBG() : _MyTex(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"PauseBG", L"Image\\Screen_Pause.png");
}

MainBG::~MainBG()
{
}

void MainBG::Update()
{
}

void MainBG::Render()
{
	Graphics g(renderSystem->_backDC);
	int endX = (int)_MyTex->Width();
	int endY = (int)_MyTex->Height();

	g.DrawImage(_MyTex->GetImage(),
		0, 0,
		endX, endY
	);
}
