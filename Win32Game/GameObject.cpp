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

void GameObject::CreateText()
{
	_Text = new Text(12,Color(255,255,255,255));
	_Text->_Owner = this;
}

void GameObject::CreateAnimater(std::wstring name)
{
	_Animater = new Animation(name,0.2f);
	_Animater->_Owner = this;
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