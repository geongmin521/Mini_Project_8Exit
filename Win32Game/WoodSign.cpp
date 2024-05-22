#include "WoodSign.h"

WoodSign::WoodSign() : _MyTex(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"WoodSign", L"Image\\Sign.png");
	_TextBox = new TextBox(L"3", 60, Color(255, 0, 0, 0), (int)FontType::dialog,false);
	CreateObject(_TextBox, LAYER_GROUP::INGAMEUI);
	
	_TextBox->GetTextComponent()->SetOffset(Vector3(-50, 100, 0));
}

WoodSign::~WoodSign()
{
}

void WoodSign::Init(int _SceneNum)
{
	_TextBox->GetTextComponent()->SetText(std::to_wstring(_SceneNum));
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
	_TextBox->SetLocation(Vector3((float)(startX + 200), (float)startY, 0));
	if (CheckRenderPosition(startX, startY, endX, endY) == true) {
		g.DrawImage(_MyTex->GetImage(),
			startX, startY,
			endX, endY
		);
	}
}
