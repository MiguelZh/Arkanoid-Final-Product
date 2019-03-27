#pragma once
#include <list>
#include "GameObject.h"
#include "checkML.h"
using namespace std;

class SDLApplication;
class GameState
{
protected:
	list<GameObject*> objects_;
	list<GameObject*> pendingOnDestroy_;
	SDLApplication* app = nullptr;
public:
	GameState(SDLApplication* app);
	virtual ~GameState();
	virtual void update();
	virtual void render();
	virtual bool handleEvents(SDL_Event& e);
	virtual void destroy();
	void removeGameObject(GameObject *gameObject);
};

