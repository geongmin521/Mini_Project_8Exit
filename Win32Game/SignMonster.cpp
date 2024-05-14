#include "SignMonster.h"  // 헤더 파일 포함
#include "ResourceManager.h"
#include "RenderSystem.h"
#include "Collider.h"
#include "Utility.h"
SignMonster::SignMonster() : _MyTex(nullptr)
{
    _MyTex = resourceManager->GetTexture(L"SignMonster", L"Image\\CharactorTest.bmp");
    GameObject::CreateCollider();
    GetCollider()->SetScale(Vector3((float)_MyTex->Width(), (float)_MyTex->Height(), 0));
    GetCollider()->SetOffset(Vector3((float)_MyTex->Width() / 2, (float)_MyTex->Height() / 2, 0));
}

SignMonster::~SignMonster()
{
}

void SignMonster::Update()
{
}

void SignMonster::Render()
{
    Vector3 renderPosition = camera->GetRenderPos(GameObject::GetLocation());

    Graphics g(renderSystem->_backDC);
    g.DrawImage(_MyTex->GetImage(),
        (int)renderPosition._x - (int)_MyTex->Width() / 2,
        (int)renderPosition._y - (int)_MyTex->Height() / 2,
        (int)_MyTex->Width(), (int)_MyTex->Height()
    );
    // ComponentRender();
}

void SignMonster::OnCollisionEnter(Collider* collider)
{
    GameObject::SetEnable(false);
}
