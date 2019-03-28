#pragma once
#include "MenuButton.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "SDLApplication.h"
class EndState : public GameState
{
protected:
	MenuButton* endButton;
	MenuButton* menuButton;
public:
	EndState(SDLApplication * app);
	virtual ~EndState();

	static void onHitMenuButton(SDLApplication* app);
	static void onHitEndButton(SDLApplication* app);
};

