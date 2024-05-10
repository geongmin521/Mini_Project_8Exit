#pragma once
namespace game
{
	class GameManager
	{
	public:
		GameManager();
		~GameManager();

		void Initialize();
		void Update();
		void FixeUpdate();
		void Render();
		void Finalize();
		void Run();

		static GameManager* GetInstance();
		static void DestroyInstance();

	private:
		static GameManager* Instance;

		int m_UpdateCount = { 0 };
		int m_FixedUpdateCount = { 0 };
	};
}