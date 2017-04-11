#pragma once

#include <stack>
#include <SFML/Graphics.hpp>

class GameState;

/*
A Game State Will Update, Draw and Handle Input.
The Manager Handles the FILO Stack of Game States.
The game will use the Game State on the top of the stack.
*/
class StateManager
{
public:

	std::stack<GameState*> StateStack;

	void PushState(GameState* st);
	void PopState();
	GameState* PeekState();
	void ChangeState(GameState* st);

	StateManager();
	~StateManager();
};

