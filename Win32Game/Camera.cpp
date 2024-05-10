#include "Camera.h"

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
}

void Camera::CalDiff()
{
}
