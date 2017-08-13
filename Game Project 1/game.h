#pragma once

#include "StateManager.h"
#include "BootLoadState.h"
#include <SFML/Graphics.hpp>
#include <assert.h>
#include "CmnStore.h"
#include <chrono>
#include "Frametimer.h"
#include "MainMenu.h"
#include "GamingState.h"
#include "Player.h"

class Game
{
private:
	/*Frame Timer*/
	Frametimer mFrameTimer;
	float mDeltaTime;

	/*State Manager*/
	StateManager mStateManager;

	/*Game Window*/
	sf::RenderWindow mWindow;

	/*States*/
	BootLoadState  mState_BootLoad;
	MainMenu mState_MainMenu;
	BoardState mState_Board;

	/*Common State Resources*/
	CmnStore mCommonStore;

	/*Player*/
	Player mPlayer;

	/*Game Functions*/
	void Update();
	void Draw();

public:
	/*Expose Player*/
	Player& GetPlayer() { return mPlayer; }

	/*Expose Window*/
	sf::RenderWindow& GetWindow() { return mWindow; }
	/*Expose Common Resource Store*/
	CmnStore& GetCommonStore() { return mCommonStore; }

	/*Expose State Manager*/
	StateManager& GetStateManager() { return mStateManager; }

	/*Expose Game States*/
	GameState& GetState_BootLoad() { return mState_BootLoad; }
	GameState& GetState_MainMenu() { return mState_MainMenu; }
	GameState& GetState_Board() { return mState_Board; }

	/*Change State*/
	void ChangeGameState(GameState& ref);
	
	/*Constructors*/
	Game();
	~Game();
};

