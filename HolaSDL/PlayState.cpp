#include "PlayState.h"
#include <time.h>
#include <stdlib.h>
#include "GameObject.h"
#include "SDLApplication.h"
PlayState::PlayState(SDLApplication* app) : GameState(app)
{
	wallTop = new Wall(WIN_WIDTH + 30, 15, Vector2D(-15, 0), app->getTexture(app->upperWallText), "Top");
	wallDer = new Wall(15, WIN_HEIGHT, Vector2D(WIN_WIDTH - 15, 0), app->getTexture(app->sideWallText), "Right");
	wallIzq = new Wall(15, WIN_HEIGHT, Vector2D(0, 0), app->getTexture(app->sideWallText), "Left");
	ball = new Ball(20, 20, Vector2D(400, 400), app->getTexture(app->ballText), { 0.5, -3 }, this);
	paddle = new Paddle(75, 15, Vector2D(270, 550), app->getTexture(app->paddleText), {0,0});
	blocksmap = new BlocksMap(WIN_WIDTH, WIN_HEIGHT, app->getTexture(app->blocksText));
	blocksmap->LeerFichero(nivelesJuego[nivelActual], false);
	rellenaLista();
}

PlayState::PlayState(SDLApplication * app, string filename) : GameState(app)
{
	ifstream file;
	file.open("..\\saves\\" + filename + ".txt");
	blocksmap = new BlocksMap(WIN_WIDTH, WIN_HEIGHT, app->getTexture(app->blocksText));
	blocksmap->LeerFichero("..\\saves\\" + filename + ".txt", true);
	float x, y, w, h, vx, vy, color;

	file >> vidas;
	file >> nivelActual;

	double velX, velY; // cogeran valor de vel
	double posX, posY; // cogeran pos
	double objectW, objectH; // medidas
	file >> velX >> velY >> posX >> posY >> objectW >> objectH;
	paddle = new Paddle(objectW, objectH, Vector2D(posX, posY), app->getTexture(app->paddleText), { velX,velY });
	file >> velX >> velY >> posX >> posY >> objectW >> objectH;
	ball = new Ball(objectW, objectH, Vector2D(posX, posY), app->getTexture(app->ballText), { velX, velY }, this);
	file >> posX >> posY >> objectW >> objectH;
	wallTop = new Wall(objectW, objectH, Vector2D(posX, posY), app->getTexture(app->upperWallText), "Top");
	file >> posX >> posY >> objectW >> objectH;
	wallIzq = new Wall(objectW, objectH, Vector2D(posX, posY), app->getTexture(app->sideWallText), "Left");
	file >> posX >> posY >> objectW >> objectH;
	wallDer = new Wall(objectW, objectH, Vector2D(posX, posY), app->getTexture(app->sideWallText), "Right");
	rellenaLista();

	file >> velX >> velY;
	for (int i = 0; i < velX*velY; i++) {
		file >> posX;
	}
	while (file.peek() != EOF) {
		file >> velX >> velY >> posX >> posY >> objectW >> objectH;
		srand((unsigned)time(0));
		int i= std::rand() / ((RAND_MAX + 1u) / 4);
		reward = new Reward(objectW, objectH, { posX, posY }, app->getTexture(app->rewardText), Vector2D(velX, velY), i, this, paddle);
		objects_.push_back(reward);
		reward = nullptr;
	}
	
	file.close();
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
	objects_.push_back(paddle);
	objects_.push_back(ball);
	objects_.push_back(wallTop);
	objects_.push_back(wallDer);
	objects_.push_back(wallIzq);
	objects_.push_back(blocksmap);
}


void PlayState::update()
{
	levelAcabado();
	if (!gameOver) {
		GameState::update();
	}
	else if (gameOver) {
		app->getStateMachine()->changeState(new EndState(app));
	}
}

bool PlayState::handleEvents(SDL_Event & e)
{
	GameState::handleEvents(e);
	if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
		if (e.key.keysym.sym == SDLK_ESCAPE) {
			app->getStateMachine()->pushState(new PauseState(app));
		}
		if (e.key.keysym.sym == SDLK_s && e.type == SDL_KEYDOWN) {
			saveGame();
		}
	}
	return false;
}


bool PlayState::collides(const SDL_Rect destRect, Vector2D & collVector, const Vector2D & vel)
{
	if (blocksmap->detectCollision(destRect, collVector, vel, this)) { return true; addPoints(); }
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
	reward = new Reward(50, 30,coord, app->getTexture(app->rewardText), Vector2D(0, 2), type, this, paddle);
	objects_.push_back(reward);
	reward = nullptr;
}

void PlayState::destruyeReward(Reward * r)
{
	list<GameObject*>::iterator it = objects_.begin();
	bool found = false;
	while (!found && (it) != objects_.end()) {
		if (static_cast<Reward*>(*it) == r) {
			removeGameObject(*it);
			found = true;
		}
		else it++;
	}
}

void PlayState::pierdeVida()
{
	vidas--;
	if (vidas == 0) {
		gameOver = true;
	}
}

void PlayState::ganaVida()
{
	vidas++;
}

void PlayState::pasaNivel()
{
	if (nivelActual < 2) {
		ball->setIni();
		nivelActual++;
		removeGameObject(blocksmap);
		blocksmap = new BlocksMap(WIN_WIDTH, WIN_HEIGHT, app->getTexture(app->blocksText));
		blocksmap->LeerFichero(nivelesJuego[nivelActual], false);
		objects_.push_back(blocksmap);
	}
	else {
		gameOver = true;
	}
}
void PlayState::levelAcabado()
{
	if (blocksmap->getBloques() == 0 && nivelActual < 2) {
		ball->setIni();
		nivelActual++;
		removeGameObject(blocksmap);
		blocksmap = new BlocksMap(WIN_WIDTH, WIN_HEIGHT, app->getTexture(app->blocksText));
		blocksmap->LeerFichero(nivelesJuego[nivelActual], false);
		objects_.push_back(blocksmap);
	}
	else if( nivelActual == 3){
		gameOver = true;
	}
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

void PlayState::addPoints()
{
	puntos++;
}


void PlayState::saveGame()
{
	cout << "Escribe el nombre del fichero donde guardar la partida:" << endl;
	string filename;
	cin >> filename;
	filename = "..\\saves\\" + filename + ".txt";

	ofstream outfile(filename, ofstream::trunc);
	outfile << vidas << " ";
	outfile << nivelActual << endl;
	for (auto object : objects_)
	{
		ArkanoidObject* a = static_cast<ArkanoidObject*>(object);
		a->saveToFile(outfile);
	}
	outfile.close();
}
