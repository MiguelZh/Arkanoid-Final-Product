#pragma once
#include "MenuButton.h"
#include "checkML.h"
#include "GameState.h"
#include "SDLApplication.h"
#include "PlayState.h"
class MainMenuState : public GameState
{
protected:
	MenuButton* playButton;
	MenuButton* loadButton;
	MenuButton* endButton;

	// imagen de inicio
	SDL_Rect titleImage;
	Texture* titleTexture = nullptr;
public:
	MainMenuState(SDLApplication * app);
	virtual ~MainMenuState();

	void render();
	static void onHitPlayButton(SDLApplication* app);
	static void onHitLoadButton(SDLApplication* app);
	static void onHitEndButton(SDLApplication* app);
};

