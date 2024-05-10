#include "GameManager.h"
#include "Win32GameProject.h"
#include "SceneManager.h"
#include "InputSystem.h"
#include "TimeSystem.h"
#include "RenderSystem.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "EventManager.h"

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
		TimeManager::GetInstance()->InitTime();
		RenderSystem::GetInstance()->InitRender();
		PathManager::GetInstance()->InitPath();
		SceneManager::GetInstance()->InitScene();
		CollisionManager::GetInstance()->Init();
	}

	void GameManager::Update()
	{
		InputSystem::GetInstance()->UpdateMouse();
		InputSystem::GetInstance()->UpdateKey();
		SceneManager::GetInstance()->Update();
		CollisionManager::GetInstance()->Update();
		InputSystem::GetInstance()->ResetInput();
	}

	void GameManager::FixeUpdate()
	{
		
	}

	void GameManager::Render()
	{
		RenderSystem::GetInstance()->StartDraw();
		SceneManager::GetInstance()->Render();
		RenderSystem::GetInstance()->EndDraw();
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
				TimeManager::GetInstance()->UpdateTime();

				FixeUpdate();

				Update();

				Render();

				EventManager::GetInstance()->Update();
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