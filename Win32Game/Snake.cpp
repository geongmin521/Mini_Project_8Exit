#include "Snake.h"
#include "ResourceManager.h"
#include "Collider.h"


Snake::Snake() : _MyTex(nullptr)
{
	_MyTex = resourceManager->GetTexture(L"Snake", L"Image\\Snake.png");
	CreateCollider();
	
	GetCollider()->SetScale(Vector3((float)_MyTex->Width(), 2300.0f, 0));
	SetName(L"Snake");
	GetCollider()->SetTrigger(true);
	GameObject::CreateAnimater(L"Snake", 0.1f);
	SetFlipX(true);
}

Snake::~Snake()
{
}

void Snake::Update()
{
	if (_State == SNAKE_STATE::CHASE) {
		float moveDistance = _MoveSpeed * timeManager->GetDeltaTime();
		SetLocation(GetLocation() + _RunDir * moveDistance);
		_MaxDistance -= moveDistance;
		if (_MaxDistance <= 0)
		{
			GetCollider()->SetPos(Vector3( - 10000, -10000, 0));
			SetEnable(false);
			Music::soundManager->StopMusic(Music::eSoundChannel::SnakeMove);//음악 재생
		}
	}
	else if (_State == SNAKE_STATE::MOVEDOWN) {
		SetLocation(GetLocation() + Vector3(0, 1, 0) * _MoveSpeed * timeManager->GetDeltaTime());
		if (GetLocation()._y >= 300) {
			ChangeState(SNAKE_STATE::WAIT);
		}
	}
	else if (_State == SNAKE_STATE::WAIT) {
		_CoolTime -= timeManager->GetDeltaTime();
		if (_CoolTime <= 0) {
			ChangeState(SNAKE_STATE::CHASE);
			_CoolTime = 1.2f;
		}
	}
	GetAinmater()->Update();
}

void Snake::ChangeState(SNAKE_STATE state)
{
	if (_State == state) //기존상태와 같으면 넘기기
		return;
	_State = state;
	if (GetAinmater() != nullptr)
	{
		std::wstring stateStr;
		if (SNAKE_STATE::CHASE == _State)
		{
			stateStr = L"Move";
			Music::soundManager->PlayMusic(Music::eSoundList::Snake_moving, Music::eSoundChannel::SnakeMove);//음악 재생
		}
		else
		{
			stateStr = L"Idle";
			if (SNAKE_STATE::MOVEDOWN == _State)
				Music::soundManager->PlayMusic(Music::eSoundList::Snake_drop_from_Web , Music::eSoundChannel::Effect);//음악 재생//이거를 각 오브젝트가 처리하는게 맞나?
		}
		GetAinmater()->ChangeState(stateStr);
	}
}

void Snake::Render()
{
	Vector3 renderPosition = camera->GetRenderPos(GameObject::GetLocation());
	Graphics g(renderSystem->_backDC);

	int startX = (int)renderPosition._x - (int)_MyTex->Width() / 2;
	int startY = (int)renderPosition._y - (int)_MyTex->Height() / 2;
	int endX = (int)_MyTex->Width();
	int endY = (int)_MyTex->Height();

	
	if (GetAinmater() != nullptr)
	{
		GetAinmater()->Render();
	}
	else
	{
		if (CheckRenderPosition(startX, startY, endX, endY) == true) {
			g.DrawImage(_MyTex->GetImage(),
				startX, startY,
				endX, endY
			);
		}
	}
	
	//ComponentRender();
}

void Snake::ResetState()
{
	_MaxDistance = 6000;
	ChangeState(SNAKE_STATE::IDLE);
	GetCollider()->SetScale(Vector3((float)_MyTex->Width(), 2300.0f, 0));
	GetCollider()->SetTrigger(true);
}

void Snake::OnCollisionEnter(Collider* collider)
{
	Music::soundManager->PlayMusic(Music::eSoundList::Snake_Bite, Music::eSoundChannel::Effect);
	
	//if (_State == SNAKE_STATE::CHASE) {
	//	SceneReload();
	//}
}

void Snake::OnTriggerExit(Collider* collider)
{
	if (_State == SNAKE_STATE::IDLE && GetLocation()._x < collider->GetOwnerObject()->GetLocation()._x) {
		
		GetCollider()->SetScale(Vector3(200.0f, 170.0f, 0.0f));
		GetCollider()->SetOffset(Vector3(0, 20.0f, 0));
		_RunDir = Vector3(1, 0, 0);
		_MyTex->GetImage()->RotateFlip(RotateNoneFlipX);
		ChangeState(SNAKE_STATE::MOVEDOWN);
		GetCollider()->SetTrigger(false);
	}
}
