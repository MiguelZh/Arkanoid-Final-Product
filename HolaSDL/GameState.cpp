#include "GameState.h"


GameState::GameState(SDLApplication * app) : app(app)
{
}


GameState::~GameState()
{
	for (auto object : objects_)
	{
		delete object;
	}
}
void GameState::render() {
	for (auto object : objects_)
	{
		object->render();
	}
}
void GameState::update() {
	for (auto object : objects_)
	{
		object->update();
	}
}
bool GameState::handleEvents(SDL_Event& e) {
	bool handled = false;
	auto it = objects_.begin();
	while (!handled && it != objects_.end()) {
		if ((*it)->handleEvent(e)) {
			handled = true;
		}
		else {
			++it;
		}
	}
	return handled;
}
