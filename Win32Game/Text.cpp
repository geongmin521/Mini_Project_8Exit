#include "Text.h"

Text::Text(int FontSize,Gdiplus::Color color, int fonttype): _Owner(nullptr)
{
	_FontSize = FontSize;
	_color = color;
	_FontType = (FontType)fonttype;
}

Text::~Text()
{
}

void Text::Render()
{
	Graphics g(renderSystem->_backDC);
	Gdiplus::Font       _Font( &resourceManager->GetFont((int)_FontType), 12, FontStyleBold, UnitPoint); //��Ʈ ����
	Gdiplus::RectF rect = GetRect(alignX::middle, alignY::middle); //��ġ?
	SolidBrush   solidBrush(_color); //�÷�

	g.DrawString(_Text.c_str(), -1, &_Font, rect, NULL, &solidBrush);
}

void Text::FinalUpdate()
{

}

Gdiplus::RectF Text::GetRect(alignX alignX, alignY alignY)
{
	int posX = _Owner->GetLocation()._x;
	int posY = _Owner->GetLocation()._y;
	switch (alignX)
	{
	case alignX::left:
		posX -= _Rect._x / 2;
		break;
	case alignX::middle:
		break;
	case alignX::right:
		posX += _Rect._x / 2;
		break;
	}
	switch (alignY)
	{
	case alignY::top:
		posY -= _Rect._y / 2;
		break;
	case alignY::middle:
		break;
	case alignY::bottom: //�ϴ� �̷��� �ϱ��ߴµ� .. �ؽ�Ʈ�� �ø����� �ؾ��ϳ�?
		posY += _Rect._y / 2;
		break;
	}
	return Gdiplus::RectF(
		posX, 
		posY,
		posX + _Rect._x,
		posY + _Rect._y);

}

