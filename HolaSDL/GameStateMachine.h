#pragma once
#include <stack>
#include "GameState.h"
using namespace std;

class GameStateMachine
{
protected:
	stack<GameState*> stateStack;
	GameState* currentState = nullptr;
public:
	GameStateMachine();
	virtual ~GameStateMachine();
	void pushState(GameState* state);
	void changeState(GameState* state);
	void popState();
	GameState* getCurrentState();
};

