#pragma once
#include "GameObject.h"
#include "Texture.h"

class TextBox : public GameObject //�ؽ�Ʈ ������Ʈ�� ���� ������Ʈ
{
public:
	TextBox(std::wstring text);
	~TextBox();
	void Update();
	void Render();

private:
	Texture* _MyTex; 
};

