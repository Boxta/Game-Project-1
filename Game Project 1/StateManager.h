#pragma once

#include <stack>
#include <SFML/Graphics.hpp>
#include <assert.h>

class GameState;

/*
A Game State Will Update, Draw and Handle Input.
The Manager Handles the FILO Stack of Game States.
The game will use the Game State on the top of the stack.
*/
class StateManager
{
public:
	/*Hold GameStates in FILO Structure*/
	std::stack<GameState*> StateStack;

	/*Add GameState to the top of the Stack*/
	void PushState(GameState& st);
	/*Remove GameState on the top of the Stack*/
	void PopState();
	/*Return GameState on the top of the Stack*/
	GameState* PeekState();
	/*Remove GameState on the top of the Stack and Add GameState to the top of the Stack*/
	void ChangeState(GameState& st);

	StateManager();
	~StateManager();
};

