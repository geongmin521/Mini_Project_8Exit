#include "TextBox.h"

TextBox::TextBox() : _MyTex(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"123", L"Image\\PlayerDump.png");
	GameObject::CreateText();
	GetTextComponent()->SetRect(Vector3((float)_MyTex->Width(), (float)_MyTex->Height(), 0));
	if (GetTextComponent() != nullptr)
	{
		GetTextComponent()->SetText(L"Test 한글도 나오나?"); //컴포넌트랑 이름구분이 없어서 헷갈리나?
	}
}

TextBox::~TextBox()
{
}

void TextBox::Update()
{
}

void TextBox::Render()
{
	Graphics g(renderSystem->_backDC);
	g.DrawImage(_MyTex->GetImage(),
		(int)GetLocation()._x - (int)_MyTex->GetImage()->GetWidth() / 2,
		(int)GetLocation()._y - (int)_MyTex->GetImage()->GetHeight() / 2,
		(int)_MyTex->GetImage()->GetWidth(), (int)_MyTex->GetImage()->GetHeight()
	);
	if (GetTextComponent() != nullptr)
	{
		GetTextComponent()->Render();
	}
}
