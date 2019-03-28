#pragma once
#include "GameState.h"
#include "Wall.h"
#include "SDLApplication.h"
#include "Ball.h"
#include "Paddle.h"
#include "EndState.h"
#include "PauseState.h"
#include "BlocksMap.h"
#include "Reward.h"
#include "FileFormatError.h"
#include "FileNotFoundError.h"
using namespace std;
class PlayState : public GameState
{
protected:
	Wall * wallTop = nullptr,
		*wallDer = nullptr,
		*wallIzq = nullptr;
	Ball* ball = nullptr;
	Vector2D ballIniVel;
	Paddle* paddle = nullptr;
	BlocksMap* blocksmap = nullptr;
	Reward * reward = nullptr;
	int vidas = 3,
		 puntos;
	bool gameOver = false;
	int nivelActual = 0;
	string nivelesJuego[3] = { "..//maps//level01.ark","..//maps//level02.ark","..//maps//level03.ark" };
public:
	PlayState(SDLApplication * app);
	PlayState(SDLApplication* app, string filename);
	virtual ~PlayState();

	void rellenaLista();

	void update();
	bool handleEvents(SDL_Event& e);

	bool collides(const SDL_Rect destRect, Vector2D &collVector, const Vector2D &vel);

	void addRewardToList(Vector2D coord);
	void destruyeReward(Reward * r);
	void pierdeVida();
	void ganaVida();
	void pasaNivel();
	void alargarPaddle();
	void acortarPaddle();
	void resetPaddle();
	int getVidas();
	void addPoints();

	void levelAcabado();
	void saveGame();
};

