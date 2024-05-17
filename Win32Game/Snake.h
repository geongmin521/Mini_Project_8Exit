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

    float _MoveSpeed = 500.0f * 1.7f;
    float _CoolTime = 0.7f;
    Vector3 _RunDir;

    SNAKE_STATE _State = SNAKE_STATE::IDLE;
};