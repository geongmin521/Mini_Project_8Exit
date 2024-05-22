#include "Camera.h"
#include "globalheader.h"
#include "FadeIn.h"
#include "FadeOut.h"

Camera* Camera::Instance = nullptr;

Camera::Camera() : _TargetObject(nullptr)
{
    FadeIn* fadein = new FadeIn;
    _ScreenEffects.push_back(fadein);
    FadeOut* fadeout = new FadeOut;
    _ScreenEffects.push_back(fadeout);
}

Camera::~Camera()
{
    for (int i = 0; i < _ScreenEffects.size(); i++) {
        delete _ScreenEffects[i];
    }
}

Camera* Camera::GetInstance()
{
    if (Instance == nullptr) {
        Instance = new Camera;
    }
    return Instance;
}

void Camera::DestroyInstance()
{
    delete Instance;
    Instance = nullptr;
}

void Camera::Update()
{
    if (_TargetObject != nullptr) {
        if (_TargetObject->IsAlive() == false) {
            _TargetObject = nullptr;
        }
        else {
            _LookPos = _TargetObject->GetLocation();
        }
    }
    Vector3 screenSize = Vector3((float)WindowWidth, (float)WindowHeight, 0);
    Vector3 center = screenSize / 2.0f;
    _CameraPos = center + _Diff;
    CalDiff();

    for (int i = 0; i < _ScreenEffects.size(); i++) {
        if(_ScreenEffects[i]->Enable() == true) _ScreenEffects[i]->Update();
    }
}

void Camera::PlayEffect(int idx)
{
    _ScreenEffects[idx]->SetEnable(true);
    _EffectEnd = false;
}

void Camera::RenderScreenEffect()
{
    for (int i = 0; i < _ScreenEffects.size(); i++) {
        if (_ScreenEffects[i]->Enable() == true) _ScreenEffects[i]->Render();
    }
}

void Camera::CalDiff()
{
    Vector3 screenSize = Vector3((float)WindowWidth, (float)WindowHeight, 0);
    Vector3 center = screenSize / 2.0f;

    if (_LookPos._x <= 0) { // 23040
        _Diff._x = center._x * -1;
    }
    else if (_LookPos._x >= 23040.0f - WindowWidth) {
        _Diff._x = 23040.0f - WindowWidth - center._x;
    }
    else _Diff = _LookPos - center;
    _Diff._y = center._y * -1;
}
