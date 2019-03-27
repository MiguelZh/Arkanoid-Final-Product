#include "EndState.h"
#include "SDLApplication.h"


EndState::EndState(SDLApplication * app) : GameState(app)
{
	endButton = new MenuButton(150, 350, 100, 50, app->getTexture(app->quitBText), app, onHitEndButton);
	objects_.push_back(endButton);
	menuButton = new MenuButton(325, 350, 100, 50, app->getTexture(app->loadBText), app, onHitMenuButton);
	objects_.push_back(menuButton);
}


EndState::~EndState()
{
}

void EndState::onHitMenuButton(SDLApplication * app)
{
	app->getStateMachine()->changeState(new MainMenuState(app));
}

void EndState::onHitEndButton(SDLApplication * app)
{
	app->setExit(true);
}

