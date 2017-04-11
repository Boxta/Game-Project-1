#include "StateManager.h"

void StateManager::PushState(GameState* st)
{
	StateStack.push(st);
}

void StateManager::PopState()
{
	if (!StateStack.empty())
	{
		StateStack.pop();
	}
}

GameState* StateManager::PeekState()
{
	if (StateStack.empty()) return nullptr;

	return StateStack.top();
}

void StateManager::ChangeState(GameState* st)
{
	if (!StateStack.empty())
		StateStack.pop();

	StateStack.push(st);
}

StateManager::StateManager()
{
}


StateManager::~StateManager()
{
}
