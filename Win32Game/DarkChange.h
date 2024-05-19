#include "GameObject.h"
#include "ResourceManager.h" 
#include "TimeSystem.h"
#include "RenderSystem.h"
class DarkChange : public GameObject
{
public:
	DarkChange();
	~DarkChange();
	void Update();
	void Render();
	void Min();
private:

	float _Min;
	float _Down;
	float _Max;
	Texture* _MyTex;

	ResourceManager* ResourceManager;
	TimeManager* TimeManager;
};

