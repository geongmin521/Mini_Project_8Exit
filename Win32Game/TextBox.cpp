#include "TextBox.h"

TextBox::TextBox(std::wstring text) : _MyTex(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"BigTextBox", L"Image\\UI\\Chatwindow_Big.png");
	GameObject::CreateText(12, Color(255, 0, 0, 0), (int)FontType::dialog);
	GetTextComponent()->SetRect(Vector3((float)_MyTex->Width(), (float)_MyTex->Height(), 0));
	GetTextComponent()->SetText(text);
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
