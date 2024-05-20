#pragma once
#include "GameObject.h"
#include "TextBox.h"

enum class MerchantState
{
    Idle,
    Talk
};

class Merchant :
    public GameObject
{
public:
    Merchant();
    ~Merchant();
    virtual void Update();
    virtual void Render();
    virtual void ResetState();
    void OnTriggerEnter(Collider* collider);
    void OnTriggerExit(Collider* collider);
    void ChangeState(MerchantState state);
private:
    MerchantState _State;
    Texture* _MyTex;
    TextBox* _TextBox;
};

