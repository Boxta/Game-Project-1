#pragma once

#include <stack>
#include <SFML/Graphics.hpp>

class GameState;

class StateManager
{
public:

	std::stack<GameState*> StateStack;
	sf::RenderWindow* wnd;

	void PushState(GameState* st);
	void PopState();
	GameState* PeekState();
	void ChangeState(GameState* st);

	StateManager();
	~StateManager();
};

