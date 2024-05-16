#include "GameManager.h"
#include "Win32GameProject.h"
#include "SceneManager.h"
#include "InputSystem.h"
#include "TimeSystem.h"
#include "RenderSystem.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include "Camera.h"
#include "Music.h"
#include "DataRead.h"
namespace game
{

	GameManager* GameManager::Instance = nullptr;
	GameManager::GameManager()
	{
	}
	GameManager::~GameManager()
	{
	}
	void GameManager::Initialize()
	{		
		timeManager->InitTime();
		renderSystem->InitRender();
		//pathManager->InitPath();
		sceneManager->InitScene();
		collisionManager->Init();
		DataRead data = DataRead();
		data.FileDataRead();
		Music::soundManager->GetInstance();
		Music::soundManager->LoadMusic(Music::eSoundList::StartBGM, true, "Sound\\BackgroudMusic.mp3");//�������
	}

	void GameManager::Update()
	{
		inputSystem->UpdateMouse();
		inputSystem->UpdateKey();
		sceneManager->Update();
		collisionManager->Update();
		inputSystem->ResetInput();
		camera->Update();
		SetWindowText(WindowHandle, std::to_wstring(timeManager->GetFrameRate()).c_str());
	}

	void GameManager::FixeUpdate()
	{
		
	}

	void GameManager::Render()
	{
		renderSystem->StartDraw();
		sceneManager->Render();
		renderSystem->EndDraw();
	}
	void GameManager::Finalize()
	{
		TimeManager::DestroyInstance();
		SceneManager::DestroyInstance();
		RenderSystem::DestroyInstance();
	}
	void GameManager::Run()
	{
		MSG msg;
		Music::soundManager->PlayMusic(Music::eSoundList::StartBGM, Music::eSoundChannel::BGM);//���� ���
		while (true)
		{
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT) break;
				else
				{
					DispatchMessage(&msg);
				}
			}
			else
			{
				timeManager->UpdateTime();

				FixeUpdate();

				Update();

				Render();

				eventManager->Update();
			}
		}
	}

	GameManager* GameManager::GetInstance()
	{
		if (Instance == nullptr)
		{
			Instance = new GameManager();
		}
		return Instance;
	}
	void GameManager::DestroyInstance()
	{
		if (Instance != nullptr)
		{
			delete Instance;
			Instance = nullptr;
		}
	}
}