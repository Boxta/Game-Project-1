#include "Game.h"

using namespace sf;

Game::Game()
	:
	mWindow(VideoMode(1920, 1080), "SFML works!"),
	mCommonTextureStore(),
	mState_BootLoad()
{
	/*Load Common Textures*/
	/*MUST Load All Before GameState Initialisation*/
	mCommonTextureStore.AddTexture("TileSheet2", "Media\\002.png");
	mCommonTextureStore.AddTexture("BootLoadImage", "Media\\LoadingIcon.png");
	Initiate();						
}

void Game::Initiate()
{
	/*Limit Window Max Frame Rate*/
	mWindow.setFramerateLimit(60);	

	/*Initiate States*/
	mState_BootLoad.Initiate(mCommonTextureStore);
	

	/*Add States To State Manager*/
	mStateManager.PushState(mState_BootLoad);

	/*Enter Game Loop*/
	while (mWindow.isOpen())
	{
		Update();
		Draw();
	}
}

void Game::Update()
{
	mDeltaTime = mFrameTimer.Mark();

	/*Check for and Process Events*/
	Event event;
	while (mWindow.pollEvent(event))
	{
		if (event.type == Event::Closed)
			mWindow.close();
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
	mStateManager.PeekState()->Draw(mDeltaTime, mWindow);

	/*Display Graphics*/
	mWindow.display();
}


Game::~Game()
{
}
