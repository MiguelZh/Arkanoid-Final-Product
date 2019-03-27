#include "GameStateMachine.h"

using namespace std;

GameStateMachine::GameStateMachine()
{
}


GameStateMachine::~GameStateMachine()
{
	currentState = nullptr;
	while (!stateStack.empty())
	{
		delete stateStack.top();
		stateStack.pop();
	}
}
void GameStateMachine::pushState(GameState* state) {
	stateStack.push(state);
	currentState = stateStack.top();
}
void GameStateMachine::changeState(GameState* state) {
	popState();
	pushState(state);
	if (!stateStack.empty())
		currentState = stateStack.top();
}
void GameStateMachine::popState() {
	if (!stateStack.empty()) {
		delete stateStack.top();
		stateStack.pop();
		if (!stateStack.empty())
			currentState = stateStack.top();
	}
}
GameState * GameStateMachine::getCurrentState() {
	return currentState;
}
