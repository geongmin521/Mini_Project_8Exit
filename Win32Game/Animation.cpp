#include "Animation.h"

void Animation::Render()
{
	Vector3 renderPosition = camera->GetRenderPos(_Owner->GetLocation());
	Graphics g(renderSystem->_backDC);
	g.DrawImage(_AnimatedTexture[CurFrame]->GetImage(),
		(int)renderPosition._x - (int)_AnimatedTexture[CurFrame]->GetImage()->GetWidth() / 2,
		(int)renderPosition._y - (int)_AnimatedTexture[CurFrame]->GetImage()->GetHeight() / 2,
		(int)_AnimatedTexture[CurFrame]->GetImage()->GetWidth(), (int)_AnimatedTexture[CurFrame]->GetImage()->GetHeight()
	);
}

void Animation::ChangeState(std::wstring state)
{
	if (this->state == state)
		return;
	else
	{
		this->state = state;
		CurFrame = 0;
		GetTexture(name,state);
	}
} 

void Animation::Update()
{
	if (_IsEnd) //애니메이션이 끝났다면 업데이트를통해 다음프레임으로 넘어가지않기
		return;
	SetFlip();
	_AnimationTime += timeManager->GetDeltaTime();
	if (_AnimationTime >= _AnimationSpeed)
	{
		_AnimationTime -= _AnimationSpeed;
		if (_IsLoop == true)
		{
			CurFrame = (CurFrame + 1) % _AnimatedTexture.size();
		}
		else
		{
			CurFrame++;
			if (CurFrame == _AnimatedTexture.size() -1)
			{
				_IsEnd = true;
			}			
		}	
	}
}

void Animation::GetTexture(std::wstring name, std::wstring state = L"Idle")
{
	_AnimatedTexture.clear();
	int index = 0;
	while (true)//상태머신까지는 추가해야해.. 구분은.. 상태와 enum으로?
	{
		//이름_상태_번호
		std::wstring path = name + L"\\" + state + L"\\" + name + L"_" + state + L"_" + std::to_wstring(index); //스테이터스까지 여기에 더해주기?
		Texture* tx = resourceManager->GetTexture(path, L"Image\\"+ path + L".png"); //상태머신은 enum일 확률이 높은데.. 그걸 스트링으로 변경해서 넘겨야지/./
		if (tx->Width() == 0)
		{
			break;
		}
		else
		{			
			_AnimatedTexture.push_back(tx);
			index++;
		}
	}
}

void Animation::Flip(bool FilpX)
{
	for (int i = 0; i < _AnimatedTexture.size(); i++)
	{
		_AnimatedTexture[i]->SetFlipX(FilpX);
		_AnimatedTexture[i]->GetImage()->RotateFlip(RotateNoneFlipX);
	}	
}

void Animation::SetFlip() //다른데서 호출하기 싫으니까 업데이트에서 처리하기 싶고 상태와 상관없이.. 현재방향으로 
//플립하기. 
{
	if (_Owner->GetFlipX() != _AnimatedTexture[0]->GetFlipX())
	{
		Flip(!_AnimatedTexture[0]->GetFlipX());
	}
}

void Animation::FinalUpdate()
{
	SetFlip();
	_AnimationTime += timeManager->GetDeltaTime();
	if (_AnimationTime >= _AnimationSpeed)
	{
		_AnimationTime -= _AnimationSpeed;
		CurFrame = (CurFrame + 1) % _AnimatedTexture.size();
	}
}

Animation::Animation(std::wstring name,float aniSpeed) :_Owner(nullptr) //여기에 경로 받아오기
{
	_IsLoop = true; //기본적으로 false
	this->name = name;
	GetTexture(name);
	CurFrame = 0;
	_AnimationSpeed = aniSpeed;
	_AnimationTime = 0;
}
Animation::~Animation() {}