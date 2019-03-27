#pragma once
#include "MenuButton.h"
#include "GameState.h"
class PauseState : public GameState
{
protected:
	MenuButton* resumeButton;
	MenuButton* menuButton;
public:
	PauseState(SDLApplication* app);

	static void onHitResumeButton(SDLApplication* app);
	static void onHitMenuButton(SDLApplication* app);
	virtual ~PauseState();
};

