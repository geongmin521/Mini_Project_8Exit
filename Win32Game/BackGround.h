#pragma once
#include "globalheader.h"
#include "GameObject.h"
#include "Texture.h"

class BackGround : public GameObject {
public:
	BackGround();
	~BackGround();

	virtual void Update();
	virtual void Render();

private:
	Texture* _MyTex;
};