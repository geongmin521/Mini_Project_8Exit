#pragma once
#include "GameObject.h"
#include "Texture.h"

class TextBox : public GameObject //텍스트 컴포넌트를 가질 오브젝트
{
public:
	TextBox(std::wstring text, int fontSize, Color color, int fontType, bool DrawBack = true, bool Big = false);
	~TextBox();
	void Update();
	void Render();

private:
	Texture* _MyTex; 
	bool _DrawBack;
};

