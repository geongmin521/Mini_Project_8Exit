#pragma once
#include "GameObject.h"
#include "Texture.h"

enum class SNAKE_STATE {
    IDLE,
    MOVEDOWN,
    WAIT,
    CHASE,
};

class Snake :
    public GameObject
{
public:
    Snake();
    ~Snake();

    virtual void Update();
    virtual void Render();

    void OnCollisionEnter(Collider* collider);
    void OnCollisionExit(Collider* collider);

private:
    Texture* _MyTex;

    float _MoveSpeed = 1080.0f;
    float _CoolTime = 1;
    Vector3 _RunDir;

    SNAKE_STATE _State = SNAKE_STATE::IDLE;
};