#pragma once
#include "GameObject.h"
#include "Texture.h"

enum class SPIDER_STATE {
    IDLE,
    WAIT,
    MOVEDOWN,
    RUN,
};

class Spider2 :
    public GameObject
{
public:
    Spider2();
    ~Spider2();

    virtual void Update();
    virtual void Render();
    virtual void ResetState();

    virtual void OnTriggerExit(Collider* collider);

private:
    Texture* _MyTex;
    SPIDER_STATE _State;
    float _CoolTime;
    float _MoveSpeed = 500.0f * 1.7f;
};

