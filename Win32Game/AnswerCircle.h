#pragma once
#include "GameObject.h"
#include "Texture.h"

class AnswerCircle : public GameObject
{
public:
	AnswerCircle();
	~AnswerCircle();
	void Update();
	void Render();

private:
	Texture* _MyTex;

};

