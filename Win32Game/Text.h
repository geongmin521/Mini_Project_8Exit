#pragma once
#include "RenderSystem.h"
#include "Camera.h"
#include "Texture.h"
//#include "ResourceManager.h"
#include "GameObject.h"
enum class alignX
{
	left,
	middle,
	right
};

enum class alignY
{
	top,
	middle,
	bottom
};

enum class FontType
{
	title,
	dialog
};

class Text
{
public: //불러오는거?
	Text(int FontSize, Gdiplus::Color color, int fonttype);
	~Text();
	void Render();
	void SetText(std::wstring text) { _Text = text; }
	void SetRect(Vector3 size) { _Rect = size; }
	void FinalUpdate();
	std::wstring GetText() { return _Text; }
	Gdiplus::RectF GetRect(alignX alignX, alignY alignY);
private:
	GameObject* _Owner;	
	std::wstring _Text; 
	Vector3 _Rect; //z는 무시 (안씀)
	int _FontSize;
	FontType _FontType;
	Gdiplus::Color _color;

	friend class GameObject;
};

