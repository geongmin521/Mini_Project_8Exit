#pragma once
#include "globalheader.h"
#include "GameObject.h"
#include "Texture.h"

class MainBackGround : public GameObject {
public:
	MainBackGround();
	~MainBackGround();

	
	virtual void Update();
	virtual void Render();

private:
	Texture* _MyTex;
	
};