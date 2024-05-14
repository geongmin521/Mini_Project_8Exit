#include "Text.h"

Text::Text(int FontSize,Gdiplus::Color color): _Owner(nullptr)
{
	_FontSize = FontSize;
	_color = color;
}

Text::~Text()
{
}

void Text::Render()
{
	Graphics g(renderSystem->_backDC);

	Gdiplus::FontFamily _FontFamily(L"Arial"); //폰트 이름?
	Gdiplus::Font       _Font(&_FontFamily, 12, FontStyleBold, UnitPoint); //폰트 설정
	Gdiplus::RectF rect = GetRect(alignX::left, alignY::bottom); //위치?
	SolidBrush   solidBrush(_color); //컬러

	g.DrawString(_Text.c_str(), -1, &_Font, rect, NULL, &solidBrush);
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
	case alignY::bottom: //일단 이렇게 하긴했는데 .. 텍스트도 플립으로 해야하나?
		posY += _Rect._y / 2;
		break;
	}
	return Gdiplus::RectF(
		posX, 
		posY,
		posX + _Rect._x,
		posY + _Rect._y);

}

