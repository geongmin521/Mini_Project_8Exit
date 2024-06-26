#pragma once
#include "GameObject.h"
#include "Texture.h"

class Spider1 :
    public GameObject
{
public:
    Spider1();
    ~Spider1();

    virtual void Update();
    virtual void Render();
    virtual void ResetState();

    void SetStopLoc(float y);

    void OnTrigger(Collider* collider);

private:
    Texture* _MyTex;

    Vector3 _PrevPosition;

    float _StopLoc;

    bool _MoveDown = false;

    void ChangeImage();
};

