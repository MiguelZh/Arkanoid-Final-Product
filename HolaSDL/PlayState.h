#pragma once
#include "GameState.h"
#include "Wall.h"
#include "SDLApplication.h"
#include "Ball.h"
#include "Paddle.h"
#include "PauseState.h"
#include "BlocksMap.h"
#include "Reward.h"
class PlayState : public GameState
{
protected:
	Wall * wallTop = nullptr,
		*wallDer = nullptr,
		*wallIzq = nullptr;
	Ball* ball = nullptr;
	Paddle* paddle = nullptr;
	BlocksMap* blocksmap = nullptr;
	Reward * reward = nullptr;
	int vidas = 3;
public:
	PlayState(SDLApplication * app);
	//PlayState(SDLApplication* app, string filename); TODO
	virtual ~PlayState();

	void rellenaLista();

	bool handleEvents(SDL_Event& e);

	bool collides(const SDL_Rect destRect, Vector2D &collVector, const Vector2D &vel);

	void addRewardToList(Vector2D coord);
	void restruyeReward();
	void pierdeVida();
	void ganaVida();
	void pasaNivel();
	void alargarPaddle();
	void acortarPaddle();
	void resetPaddle();
	int getVidas();
};

