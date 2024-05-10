#include "GameObject.h"
#include "Collider.h"

GameObject::GameObject() : _Location(0, 0, 0), _Scale(0, 0, 0), _Name(L""), _Collider(nullptr)
{
}
GameObject::~GameObject() 
{
	if (_Collider != nullptr) {
		delete _Collider;
	}
}

void GameObject::CreateCollider()
{
	_Collider = new Collider;
	_Collider->_Owner = this;
}

void GameObject::FinalUpdate()
{
	if (_Collider != nullptr) {
		_Collider->FinalUpdate();
	}
}

void GameObject::ComponentRender()
{
	if (_Collider != nullptr) {
		_Collider->Render();
	}
}