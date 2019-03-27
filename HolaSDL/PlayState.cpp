#include "PlayState.h"
#include <time.h>
#include <stdlib.h>


PlayState::PlayState(SDLApplication* app) : GameState(app)
{
	wallTop = new Wall(WIN_WIDTH + 30, 15, Vector2D(-15, 0), app->getTexture(app->upperWallText), "Top");
	wallDer = new Wall(15, WIN_HEIGHT, Vector2D(WIN_WIDTH - 15, 0), app->getTexture(app->sideWallText), "Right");
	wallIzq = new Wall(15, WIN_HEIGHT, Vector2D(0, 0), app->getTexture(app->sideWallText), "Left");
	ball = new Ball(20, 20, Vector2D(400, 500), app->getTexture(app->ballText), { 0, -3 }, this);
	paddle = new Paddle(75, 15, Vector2D(270, 550), app->getTexture(app->paddleText), {0,0});
	blocksmap = new BlocksMap(WIN_WIDTH, WIN_HEIGHT, app->getTexture(app->blocksText));
	blocksmap->LeerFichero("..//maps//level03.ark", false);
	rellenaLista();
}


PlayState::~PlayState()
{
	wallTop = nullptr,
		wallDer = nullptr,
		wallIzq = nullptr;
	ball = nullptr;
}

void PlayState::rellenaLista()
{
	//objetos iniciales
	objects_.push_back(wallTop);
	objects_.push_back(wallDer);
	objects_.push_back(wallIzq);
	objects_.push_back(ball);
	objects_.push_back(paddle);
	objects_.push_back(blocksmap);
}

bool PlayState::handleEvents(SDL_Event & e)
{
	GameState::handleEvents(e);
	if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
		if (e.key.keysym.sym == SDLK_ESCAPE) {
			app->getStateMachine()->pushState(new PauseState(app));
		}
		if (e.key.keysym.sym == SDLK_s) {
			//saveGame();
		}
	}
	return false;
}


bool PlayState::collides(const SDL_Rect destRect, Vector2D & collVector, const Vector2D & vel)
{
	if (blocksmap->detectCollision(destRect, collVector, vel, this)) return true;
	if (wallDer->collides(destRect, collVector)) return true;
	if (wallIzq->collides(destRect, collVector)) return true;
	if (wallTop->collides(destRect, collVector)) return true;
	if (paddle->collides(destRect, collVector)) return true;
	return false;
}

void PlayState::addRewardToList(Vector2D coord)
{
	srand(time(NULL));
	int type = rand() % 4;
	reward = new Reward(50, 30,coord, app->getTexture(app->rewardText), Vector2D(0, 2), type, this);
	objects_.push_back(reward);
	reward = nullptr;
}

void PlayState::restruyeReward()
{

}

void PlayState::pierdeVida()
{
	vidas--;
}

void PlayState::ganaVida()
{
	vidas++;
}

void PlayState::pasaNivel()
{

}

void PlayState::alargarPaddle()
{
	paddle->resetWidth();
	paddle->setWidth(90);
}

void PlayState::acortarPaddle()
{
	paddle->resetWidth();
	paddle->setWidth(60);
}

void PlayState::resetPaddle()
{
	paddle->resetWidth();
}

int PlayState::getVidas()
{
	return vidas;
}
