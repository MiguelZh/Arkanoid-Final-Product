#pragma once
#include "SDL.h"
#include "checkML.h"

typedef unsigned int uint;
class SDLApplication;
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();
	virtual void render() = 0;
	virtual void update() = 0;
	virtual bool handleEvent(SDL_Event& e) = 0;
};

