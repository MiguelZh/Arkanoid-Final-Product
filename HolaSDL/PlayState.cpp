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
	ball = new Ball(20, 20, Vector2D(400, 500), app->getTexture(app->ballText), { 0, -3 }, this);
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
	int a, b;
	file >> a; file >> b;
	ballIniVel = { (double)a ,(double)b };
	file >> a; file >> b;
	int c, d; file >> c; file >> d;
	paddle = new Paddle(c, d, { (double)a,(double)b }, app->getTexture(app->paddleText), ballIniVel);
	file >> a; file >> b;
	ballIniVel = { (double)a ,(double)b };
	file >> a; file >> b;
	file >> c; file >> d;
	ball = new Ball(20, 20, { (double)d,(double)c }, app->getTexture(app->ballText), ballIniVel, this);
	wallTop = new Wall(WIN_WIDTH + 30, 15, Vector2D(-15, 0), app->getTexture(app->upperWallText), "Top");
	wallDer = new Wall(15, WIN_HEIGHT, Vector2D(WIN_WIDTH - 15, 0), app->getTexture(app->sideWallText), "Right");
	wallIzq = new Wall(15, WIN_HEIGHT, Vector2D(0, 0), app->getTexture(app->sideWallText), "Left");
	file.close();
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


void PlayState::update()
{
	GameState::update();
	levelAcabado();
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
	if (vidas == 1 ) {
		cout << "Has perdido!" << endl;
		app->getStateMachine()->changeState(new EndState(app));
	}
	vidas--;
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
		app->getStateMachine()->changeState(new EndState(app));
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
	else if( nivelActual == 2){
		app->getStateMachine()->changeState(new EndState(app));
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
	system("cls");
	cout << "Escribe el nombre del archivo: " << endl;
	string nombre;
	cin >> nombre;
	string filename = "..\\saves\\" + nombre + ".txt";
	ofstream file(filename, ofstream::trunc); // borra todo lo que ya este guardado, si existe un archivo igual
	// tamaño paddle, bola,walltop,wallder,wallizq,mapa
	for (auto *n : objects_) {
		ArkanoidObject * object = static_cast<ArkanoidObject*>(n);
		object->saveToFile(file);
	}
	file.close();
}
