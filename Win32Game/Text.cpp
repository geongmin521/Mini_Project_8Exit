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
	Gdiplus::Font       _Font( &resourceManager->GetFont((int)_FontType), (Gdiplus::REAL)_FontSize, FontStyleBold, UnitPoint); //폰트 설정
	Gdiplus::RectF rect = GetRect(alignX::middle, alignY::middle); //위치?
	SolidBrush   solidBrush(_color); //컬러
	//rect = RectF(0, 0, 100, 100);
	g.DrawString(_Text.c_str(), -1, &_Font, rect, NULL, &solidBrush);
}

void Text::FinalUpdate()
{

}

Gdiplus::RectF Text::GetRect(alignX alignX, alignY alignY)
{
	int posX = (int)(_Owner->GetLocation()._x + _Offset._x);
	int posY = (int)(_Owner->GetLocation()._y + _Offset._y);
	switch (alignX)
	{
	case alignX::left:
		posX -= (int)(_Rect._x / 2.0f);
		break;
	case alignX::middle:
		break;
	case alignX::right:
		posX += (int)(_Rect._x / 2.0f);
		break;
	}
	switch (alignY)
	{
	case alignY::top:
		posY -= (int)(_Rect._y / 2.0f);
		break;
	case alignY::middle:
		break;
	case alignY::bottom: //일단 이렇게 하긴했는데 .. 텍스트도 플립으로 해야하나?
		posY += (int)(_Rect._y / 2.0f);
		break;
	}
	return Gdiplus::RectF(
		(Gdiplus::REAL)posX, 
		(Gdiplus::REAL)posY,
		(Gdiplus::REAL)((int)_Rect._x),
		(Gdiplus::REAL)((int)_Rect._y));

}

