#pragma once

#include "StateManager.h"
#include "TestState.h"
#include <SFML/Graphics.hpp>
#include <assert.h>
#include "CmnTextureStore.h"
#include <chrono>
#include "Frametimer.h"

class Game
{
private:
	/*Frame Timer*/
	Frametimer mFrameTimer;
	float mDeltaTime;

	/*State Manager*/
	StateManager mStateManager = {};

	/*Game States*/
	//TestState mTestState;

	/*Game Window*/
	sf::RenderWindow mWindow;
	
	/*Game Functions*/
	void Initiate();
	void Update();
	void Draw();

public:
	/*Common State Resources*/
	CmnTextureStore mCommonTextureStore;
	sf::Font mFont_System;
	/*Constructors*/
	Game();
	~Game();
};

