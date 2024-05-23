#include "TextBox.h"

TextBox::TextBox(std::wstring text, int fontSize, Color color, int fontType, bool DrawBack, bool Big) : _MyTex(nullptr)
{
	this->_DrawBack = DrawBack;
	if (Big == false)
	{
		_MyTex = resourceManager->GetTexture(L"SmallTextBox", L"Image\\UI\\Chatwindow_Small.png");
	}
	else
	{
		_MyTex = resourceManager->GetTexture(L"BigTextBox", L"Image\\UI\\Chatwindow_Big.png");
	}
	GameObject::CreateText(fontSize, color, fontType);
	GetTextComponent()->SetRect(Vector3((float)_MyTex->Width() - 100 , (float)_MyTex->Height(), 0));
	GetTextComponent()->SetText(text);
	GetTextComponent()->SetOffset(Vector3(-180,-40,0));

}

TextBox::~TextBox()
{
}

void TextBox::Update()
{
}

void TextBox::Render()
{
	if (_DrawBack)
	{
		Graphics g(renderSystem->_backDC);
		g.DrawImage(_MyTex->GetImage(),
			(int)GetLocation()._x - (int)_MyTex->GetImage()->GetWidth() / 2,
			(int)GetLocation()._y - (int)_MyTex->GetImage()->GetHeight() / 2,
			(int)_MyTex->GetImage()->GetWidth(), (int)_MyTex->GetImage()->GetHeight()
		);
	}
	if (GetTextComponent() != nullptr)
	{
		GetTextComponent()->Render();
	}
}
