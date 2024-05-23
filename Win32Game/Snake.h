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
    virtual void ResetState();
    void ChangeState(SNAKE_STATE state);
    void OnCollisionEnter(Collider* collider);
    void OnTriggerExit(Collider* collider);

private:
    Texture* _MyTex;
    float _MaxDistance;
    float _MoveSpeed = 500.0f * 1.7f;
    float _CoolTime = 1.2f;
    Vector3 _RunDir;

    SNAKE_STATE _State = SNAKE_STATE::IDLE;
};