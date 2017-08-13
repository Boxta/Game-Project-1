#include "Game.h"

using namespace sf;

Game::Game()
	:
	mWindow(sf::VideoMode(1920, 1080), "Battle Cards", sf::Style::Fullscreen),
	mCommonStore(),
	mStateManager(*this),
	mState_BootLoad(*this),
	mState_Board(*this),
	mState_MainMenu(*this),
	mPlayer(*this)
{
	/*Set Initial State To State Manager*/
	ChangeGameState(mState_BootLoad);

	/*Initiate States*/
	for (auto& s : mStateManager.StateStack._Get_container())
	{
		s->Initiate();
	}

	/*Enter Game Loop*/
	while (mWindow.isOpen())
	{
		Update();
		Draw();
	}
}

void Game::ChangeGameState(GameState & ref)
{
	mStateManager.ChangeState(ref);
	mStateManager.PeekState()->Initiate();
}

void Game::Update()
{
	/*Time Since Last Update Call*/
	mDeltaTime = mFrameTimer.Mark();

	/*Check for and Process Events*/
	Event event;
	while (mWindow.pollEvent(event))
	{
		if (event.type == Event::Closed)
			mWindow.close();

		mStateManager.PeekState()->HandleEvents(event);
	}
	/*Assert there is always a game state in the stack*/
	assert(mStateManager.PeekState() != nullptr);

	/*Handle Input Then Update State @ Top Of Stack*/
	mStateManager.PeekState()->HandleInput();

	mStateManager.PeekState()->Update(mDeltaTime);
}

void Game::Draw()
{
	/*Draw State @ Top Of Stack*/
	mStateManager.PeekState()->Draw();

	/*Display Graphics*/
	mWindow.display();
}

Game::~Game()
{
}
