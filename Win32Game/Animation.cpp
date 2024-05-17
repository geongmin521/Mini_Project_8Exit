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
	_AnimationTime += timeManager->GetDeltaTime();
	if (_AnimationTime >= _AnimationSpeed)
	{
		_AnimationTime -= _AnimationSpeed;
		CurFrame = (CurFrame + 1) % _AnimatedTexture.size();
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

Animation::Animation(std::wstring name,float aniSpeed) :_Owner(nullptr) //여기에 경로 받아오기
{
	this->name = name;
	GetTexture(name);
	CurFrame = 0;
	_AnimationSpeed = aniSpeed;
	_AnimationTime = 0;
}
Animation::~Animation() {}