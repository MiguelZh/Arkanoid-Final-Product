#include "EndState.h"
EndState::EndState(SDLApplication * app) : GameState(app)
{
	endButton = new MenuButton(200, 350, 100, 50, app->getTexture(app->quitBText), app, onHitEndButton);
	objects_.push_back(endButton);
	menuButton = new MenuButton(500, 350, 100, 50, app->getTexture(app->menuBText), app, onHitMenuButton);
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

