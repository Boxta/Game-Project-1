#include "Game.h"

using namespace sf;

Game::Game()
	:
	mWindow(VideoMode(1920, 1080), "Card Battle"),
	mCommonTextureStore(),
	mStateManager(*this),
	mState_BootLoad(mStateManager, mWindow),
	mState_Board(mStateManager, mWindow),
	mState_MainMenu(mStateManager, mWindow)
{
	/*Load Common Textures*/
	mCommonTextureStore.AddTexture("MenuBackground", "Media\\Background2.png");
	mCommonTextureStore.AddTexture("BoardBackground", "Media\\Background1.png");
	mCommonTextureStore.AddTexture("BootLoadImage", "Media\\LoadingIcon.png");
	mCommonTextureStore.AddTexture("BaseButtons", "Media\\BaseButtons.png");

	/*Initiate Game*/
	Initiate();						
}

void Game::ChangeGameState(GameState & ref)
{
	mStateManager.PushState(ref);
	mStateManager.PeekState()->Initiate();
}

void Game::Initiate()
{
	/*Limit Window Max Frame Rate*/
	mWindow.setFramerateLimit(60);	
	
	/*Add States To State Manager*/
	mStateManager.PushState(mState_MainMenu);
	mStateManager.PushState(mState_BootLoad);
	
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
