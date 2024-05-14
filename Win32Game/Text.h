#pragma once
#include "RenderSystem.h"
#include "Camera.h"
#include "Texture.h"
#include "ResourceManager.h"
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

class Text
{
public: //�ҷ����°�?
	Text(int FontSize, Gdiplus::Color color);
	~Text();
	void Render();
	std::wstring GetText() { return _Text; }
	void SetText(std::wstring text) { _Text = text; }
	Gdiplus::RectF GetRect(alignX alignX, alignY alignY);
	void SetRect(Vector3 size) { _Rect = size; }
private:
	GameObject* _Owner;	
	std::wstring _Text; 
	Vector3 _Rect; //z�� ���� (�Ⱦ�)
	int _FontSize;
	Gdiplus::Color _color;


	friend class GameObject;
};

