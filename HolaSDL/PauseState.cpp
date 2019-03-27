#include "PauseState.h"
#include "SDLApplication.h"

PauseState::PauseState(SDLApplication* app) : GameState(app)
{
	resumeButton = new MenuButton(200, 200, 150, 150,app->getTexture(app->resumeBText),app, onHitResumeButton);
	menuButton = new MenuButton(500, 200, 125, 125, app->getTexture(app->endBText), app, onHitMenuButton);
	objects_.push_back(resumeButton);
	objects_.push_back(menuButton);
}

void PauseState::onHitResumeButton(SDLApplication * app)
{
	app->getStateMachine()->popState();
}

void PauseState::onHitMenuButton(SDLApplication * app)
{
	app->getStateMachine()->changeState(new MainMenuState(app));
}


PauseState::~PauseState()
{
	resumeButton = nullptr;
	menuButton = nullptr;
}

