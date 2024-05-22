#include "ScareCrow_Search.h"
#include "Collider.h"

ScareCrow_Search::ScareCrow_Search()
{
	CreateCollider();
	GetCollider()->SetScale(Vector3(3840.0f, 500.0f, 0));
	GetCollider()->SetPos(Vector3(-10000.0f, -10000.0f, 0));
	GetCollider()->SetTrigger(true);
}

ScareCrow_Search::~ScareCrow_Search()
{
}

void ScareCrow_Search::Update()
{

}

void ScareCrow_Search::Render()
{
	ComponentRender();
}

void ScareCrow_Search::OnTrigger(Collider* collider)
{
	_PlayerDir = collider->GetOwnerObject()->GetDir();
	_PlayerLocation = collider->GetOwnerObject()->GetLocation();
}
