#include "Witch.h"
#include "ResourceManager.h"
#include "Camera.h"


Witch::Witch() : _MyTex(nullptr)
{
    _MyTex = resourceManager->GetTexture(L"Witch", L"Image\\Witch.png");
    SetLocation(Vector3(1200, 400, 0));
}

Witch::~Witch() 
{
}

void Witch::Update()
{
}

void Witch::Render()
{
    Vector3 renderPosition = camera->GetRenderPos(GameObject::GetLocation());
    Graphics g(renderSystem->_backDC);

    int startX = (int)renderPosition._x - (int)_MyTex->Width() / 2;
    int startY = (int)renderPosition._y - (int)_MyTex->Height() / 2;
    int endX = (int)_MyTex->Width();
    int endY = (int)_MyTex->Height();

    if (CheckRenderPosition(startX, startY, endX, endY))
    {
        g.DrawImage(_MyTex->GetImage(), startX, startY, endX, endY);
    }
    ComponentRender();
}

