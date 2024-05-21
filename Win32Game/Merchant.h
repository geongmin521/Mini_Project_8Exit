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
    void Init();
    virtual void Update();
    virtual void Render();
    virtual void ResetState();
    void OnTriggerEnter(Collider* collider);
    void OnTriggerExit(Collider* collider);
    void ChangeState(MerchantState state);
    void ChangeImage();
private:
    MerchantState _State;
    Texture* _MyTex;
    TextBox* _TextBox;
};

