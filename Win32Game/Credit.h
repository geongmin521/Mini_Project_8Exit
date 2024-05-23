#pragma once
#include "GameObject.h"

class Credit :
    public GameObject
{
public:
    Credit();
    ~Credit();

    virtual void Update();
    virtual void Render();

private:
    Gdiplus::Image* _ImgConnect;
    UINT _Count;
    GUID* _DimentionIDs;
    UINT _FrameCount;
    UINT _Idx;
    UINT _ImageIdx;

    bool _StartTimer = false;
    float _Timer;
    float _GifNextTimer;
};

