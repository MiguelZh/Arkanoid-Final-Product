#include "MainMenuState.h"



MainMenuState::MainMenuState(SDLApplication * app): GameState(app)
{
	playButton = new MenuButton(150, 350, 100, 50, app->getTexture(app->menuBText), app, onHitPlayButton);
	objects_.push_back(playButton);
	loadButton = new MenuButton(325, 350, 100, 50, app->getTexture(app->loadBText), app, onHitLoadButton);
	objects_.push_back(loadButton);
	endButton = new MenuButton(500, 350, 100, 50, app->getTexture(app->endBText), app, onHitEndButton);
	objects_.push_back(endButton);
	titleTexture = app->getTexture(app->titleText);
}


MainMenuState::~MainMenuState()
{
}

void MainMenuState::render() {
	GameState::render();

	// imagen de inicio
	titleImage.x = 200;
	titleImage.y = 10;
	titleImage.h = 200;
	titleImage.w = 400;
	titleTexture->render(titleImage);
}

void MainMenuState::onHitPlayButton(SDLApplication* app) {
	app->getStateMachine()->changeState(new PlayState(app));
}

void MainMenuState::onHitEndButton(SDLApplication* app) {
	app->setExit(true);
}

void MainMenuState::onHitLoadButton(SDLApplication* app) {
	cout << " Nombre del archivo que quiere cargar: " << endl;
	string filename;
	cin >> filename;
	app->getStateMachine()->changeState(new PlayState(app, filename));
}
