#pragma once

#include "StateManager.h"
#include "TestState.h"
#include <SFML/Graphics.hpp>
#include <assert.h>

class Game
{
public:
	StateManager mStateManager = {};

	/*Add State To The State Stack*/
	TestState mTestState;
	sf::RenderWindow Window;
	Game();
	void Initiate();
	void Update();
	void Draw();

	~Game();
};

