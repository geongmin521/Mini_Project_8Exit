#pragma once
#include "globalheader.h"
#include "GameObject.h"
#include "Texture.h"

class LastBackGround : public GameObject {
public:
	LastBackGround();
	~LastBackGround();


	virtual void Update();
	virtual void Render();

private:
	Texture* _MyTex;

};

