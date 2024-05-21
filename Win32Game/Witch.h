
#include "GameObject.h"
#include "Texture.h"

class Witch : public GameObject {
public:
    Witch();
    ~Witch();

    void Update();
    void Render();

private:
    Texture* _MyTex;
};


