#include "Camera.h"
#include "globalheader.h"

Camera* Camera::Instance = nullptr;

Camera::Camera() : _TargetObject(nullptr)
{
}

Camera::~Camera()
{
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
