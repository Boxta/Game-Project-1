// Game Project 1.cpp : Defines the entry point for the console application.
//

#include "game.h"

using namespace sf;

int main()
{
	TestState mTestState(&mStateManager);
	mStateManager.PushState(&mTestState);

	//Create a window passing in the window size and title bar name
	RenderWindow window(VideoMode(600, 600), "SFML works!");

	//Continue to loop while the window is open
	while (window.isOpen())
	{
		//Check for and process any events
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		//If No GameState Exists ERROR
		assert(mStateManager.PeekState() != nullptr);

		//Loop Through Game State Order
		mStateManager.PeekState()->HandleInput();
		mStateManager.PeekState()->Update(1.0f);
		mStateManager.PeekState()->Draw(1.0f, window);
		
		//Display Drawn Graphics
		window.display();
	}

	return 0;
}

