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
		DataRead data = DataRead();
		data.FileDataRead();
		timeManager->InitTime();
		renderSystem->InitRender();
		//pathManager->InitPath();
		sceneManager->InitScene();
		collisionManager->Init();		
		Music::soundManager->GetInstance();
		Music::soundManager->Init();

		Music::soundManager->LoadMusic(Music::eSoundList::Player_run, true,					"Sound\\Player_Run.mp3");
		Music::soundManager->LoadMusic(Music::eSoundList::click, false,						"Sound\\click.mp3");  
		Music::soundManager->LoadMusic(Music::eSoundList::Buttoclick, false,				"Sound\\Buttonclick.mp3");
		Music::soundManager->LoadMusic(Music::eSoundList::New_Background_music, true,		"Sound\\New_Background_music.mp3");
		Music::soundManager->LoadMusic(Music::eSoundList::Attacked_by_Objects, false,		"Sound\\Attacked_by_Objects.mp3");  
		Music::soundManager->LoadMusic(Music::eSoundList::Carriage_rush, false,				"Sound\\Carriage_rush.mp3");//배경음악
		Music::soundManager->LoadMusic(Music::eSoundList::bonfire, true,					"Sound\\bonfire.mp3");//배경음악
		Music::soundManager->LoadMusic(Music::eSoundList::Carriage_moving, true,			"Sound\\Carriage_moving.mp3");//배경음악
		Music::soundManager->LoadMusic(Music::eSoundList::Cottage_door_open, false,			"Sound\\Cottage_door_open.mp3");	
		Music::soundManager->LoadMusic(Music::eSoundList::Merchant_chat, true,				"Sound\\Merchant_chat.mp3");			
		Music::soundManager->LoadMusic(Music::eSoundList::Player_Walk, true,				"Sound\\Player_Walk.mp3");
		Music::soundManager->LoadMusic(Music::eSoundList::Scarecrow_drop_from_Web, false,	"Sound\\Scarecrow_drop_from_Web.mp3");
		Music::soundManager->LoadMusic(Music::eSoundList::Snake_drop_from_Web, false,		"Sound\\Snake_drop_from_Web.mp3");
		Music::soundManager->LoadMusic(Music::eSoundList::Snake_Bite, false,				"Sound\\Snake_Bite.mp3");
		Music::soundManager->LoadMusic(Music::eSoundList::Snake_moving, true,				"Sound\\Snake_moving.mp3");
		Music::soundManager->LoadMusic(Music::eSoundList::Stage_Transition_with_correct, false,		"Sound\\Stage_Transition_with_correct.mp3");
		Music::soundManager->LoadMusic(Music::eSoundList::Stage_Transition_with_wrong, false,		"Sound\\Stage_Transition_with_wrong.mp3");
		Music::soundManager->LoadMusic(Music::eSoundList::When_the_wrong_picture_triggered_1, false,"Sound\\When_the_wrong_picture_triggered_1.mp3"); //화면에 보여지면 소리니까 루프?
	
	}

	void GameManager::Update()
	{
		inputSystem->UpdateMouse();
		inputSystem->UpdateKey();
		sceneManager->Update();
		collisionManager->Update();
		inputSystem->ResetInput();
		camera->Update();
	}

	void GameManager::FixeUpdate()
	{
		
	}

	void GameManager::Render()
	{
		renderSystem->StartDraw();
		sceneManager->Render();
		camera->RenderScreenEffect();
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
		Music::soundManager->PlayMusic(Music::eSoundList::New_Background_music, Music::eSoundChannel::BGM);//음악 재생
		Music::soundManager->SetVolume(0.5f, Music::eSoundChannel::BGM);
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