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
	if (_IsEnd) //�ִϸ��̼��� �����ٸ� ������Ʈ������ �������������� �Ѿ���ʱ�
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
	while (true)//���¸ӽű����� �߰��ؾ���.. ������.. ���¿� enum����?
	{
		//�̸�_����_��ȣ
		std::wstring path = name + L"\\" + state + L"\\" + name + L"_" + state + L"_" + std::to_wstring(index); //�������ͽ����� ���⿡ �����ֱ�?
		Texture* tx = resourceManager->GetTexture(path, L"Image\\"+ path + L".png"); //���¸ӽ��� enum�� Ȯ���� ������.. �װ� ��Ʈ������ �����ؼ� �Ѱܾ���/./
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

void Animation::SetFlip() //�ٸ����� ȣ���ϱ� �����ϱ� ������Ʈ���� ó���ϱ� �Ͱ� ���¿� �������.. ����������� 
//�ø��ϱ�. 
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

Animation::Animation(std::wstring name,float aniSpeed) :_Owner(nullptr) //���⿡ ��� �޾ƿ���
{
	_IsLoop = true; //�⺻������ false
	this->name = name;
	GetTexture(name);
	CurFrame = 0;
	_AnimationSpeed = aniSpeed;
	_AnimationTime = 0;
}
Animation::~Animation() {}