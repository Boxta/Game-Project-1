#include "Game.h"

using namespace sf;

Game::Game()
	:
	Window(VideoMode(600, 600), "SFML works!")
{
	Initiate();
}

void Game::Initiate()
{

	mStateManager.PushState(&mTestState);
	

	/*Enter Game Loop*/
	while (Window.isOpen())
	{
		Update();
		Draw();
	}
}

void Game::Update()
{
	/*Check for and Process Events*/
	Event event;
	while (Window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			Window.close();
	}

	/*Assert there is always a game state in the stack*/
	assert(mStateManager.PeekState() != nullptr);

	/*Handle Input Then Update State @ Top Of Stack*/
	mStateManager.PeekState()->HandleInput();
	mStateManager.PeekState()->Update(1.0f);
}

void Game::Draw()
{
	/*Draw State @ Top Of Stack*/
	mStateManager.PeekState()->Draw(1.0f, Window);

	/*Display Graphics*/
	Window.display();
}


Game::~Game()
{
}
