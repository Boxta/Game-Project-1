// Game Project 1.cpp : Defines the entry point for the console application.
//

#include "game.h"

using namespace sf;

int main()
{
	/*Add State To The State Stack*/
	mStateManager.PushState(&mTestState);

	/*Create a SFML Window*/
	RenderWindow window(VideoMode(600, 600), "SFML works!");
	//window.setFramerateLimit(60);

	/*Enter Game Loop*/
	while (window.isOpen())
	{
		/*Check for and Process Events*/
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		/*Asser there is always a game state in the stack*/
		assert(mStateManager.PeekState() != nullptr);

		/*Cycle Functions on GameState at the top of the State Stack*/
		mStateManager.PeekState()->HandleInput();
		mStateManager.PeekState()->Update(1.0f);
		mStateManager.PeekState()->Draw(1.0f, window);

		/*Display Graphics*/
		window.display();
	}

	return 0;
}

