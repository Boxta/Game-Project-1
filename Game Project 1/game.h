#pragma once

#include "StateManager.h"
#include "BootLoadState.h"
#include <SFML/Graphics.hpp>
#include <assert.h>
#include "CmnTextureStore.h"
#include <chrono>
#include "Frametimer.h"
#include "MainMenu.h"
#include "BoardState.h"

class Game
{
private:
	/*Frame Timer*/
	Frametimer mFrameTimer;
	float mDeltaTime;

	/*State Manager*/
	StateManager mStateManager;

	/*Game States*/
	//TestState mTestState;
	BootLoadState  mState_BootLoad;
	MainMenu mState_MainMenu;
	BoardState mState_Board;

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

