// Game Project 1.cpp : Defines the entry point for the console application.
//

#include "game.h"
#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	//Create a window passing in the window size and title bar name
	RenderWindow window(VideoMode(600, 600), "SFML works!");

	//Create a SFML Circle shape passing in the radius
	CircleShape shape(300.f);

	//Set the color of the created shape
	shape.setFillColor(Color::Green);

	//Continue to loop while the window is open
	while (window.isOpen())
	{
		//Check for any events
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		//Clear the window before drawing
		window.clear();

		//Draw the shape to the cleared window
		window.draw(shape);

		//Render the drawn item(s) to the window and display to the user
		window.display();
	}

	return 0;
}

