#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "TextBox.h"

class WoodSign :
    public GameObject
{
public:
    WoodSign();
    ~WoodSign();
    void Init(int _SceneNum);
    virtual void Update();
    virtual void Render();

private:
    Texture* _MyTex;
    TextBox* _TextBox;
};

