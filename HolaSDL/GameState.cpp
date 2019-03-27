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

void GameState::destroy()
{
	for (auto gameObject : pendingOnDestroy_) {
		// If the gameObject was already deleted from memory,
		// skip this search
		if (gameObject == nullptr) continue;

		auto it = objects_.begin();
		while (it != objects_.end()) {
			if (*it == gameObject) {
				objects_.erase(it);
				delete gameObject;
				break;
			}
			++it;
		}
	}

	pendingOnDestroy_.clear();
}

void GameState::removeGameObject(GameObject * gameObject)
{
	pendingOnDestroy_.push_back(gameObject);
}
