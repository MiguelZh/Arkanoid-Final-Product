#pragma once
#include "SDL_image.h"
#include"Texture.h"
#include "GameStateMachine.h"
#include "SDLError.h"
#include "MainMenuState.h"
const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 600;
const int NUM_TEXTURES = 12; // SI AÑADES TEXTURAS AUMENTA ESTE NUMERO
const int FRAME_RATE = 10;
class SDLApplication
{
private:
	Texture * textures[NUM_TEXTURES];
protected:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool exit = false;
	GameStateMachine * stateMachine = nullptr;

	const string textureNames[NUM_TEXTURES] = {
		"..\\images\\bricks.png",
		"..\\images\\rewards.png",
		"..\\images\\resume.png",
		"..\\images\\quit.png",
		"..\\images\\loadButton.png",
		"..\\images\\menu.png",
		"..\\images\\end.png",
		"..\\images\\title.png",
		"..\\images\\side.png",
		"..\\images\\topside.png",
		"..\\images\\paddle.png",
		"..\\images\\ball.png"
	};	

public:
	SDLApplication();
	virtual ~SDLApplication();
	void run();
	void render();
	void update();
	void destroy();
	void handleEvents();
	Texture * getTexture(int num);
	GameStateMachine * getStateMachine();
	void setExit(bool set);

	//publico debido a que es necesario acceder a el para facilitar las cosas
	const enum textureName {
		blocksText,
		rewardText,
		resumeBText,
		quitBText,
		loadBText,
		menuBText,
		endBText,
		titleText,
		sideWallText,
		upperWallText,
		paddleText,
		ballText
	};
};

