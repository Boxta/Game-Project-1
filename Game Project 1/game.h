#pragma once

#include "StateManager.h"
#include "TestState.h"
#include <SFML/Graphics.hpp>
#include <assert.h>
#include "CmnTextureStore.h"

class Game
{
private:
	StateManager mStateManager = {};

	/*Add State To The State Stack*/
	TestState mTestState;
	sf::RenderWindow mWindow;
	
	
	void Initiate();
	void Update();
	void Draw();

public:
	CmnTextureStore mCommonTextureStore;
	Game();
	~Game();
};

