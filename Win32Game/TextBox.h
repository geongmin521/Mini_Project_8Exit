#pragma once
#include "GameObject.h"
#include "Texture.h"

class TextBox : public GameObject //�ؽ�Ʈ ������Ʈ�� ���� ������Ʈ
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

