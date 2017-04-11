#pragma once

#include <stack>
#include <SFML/Graphics.hpp>

/*
Virtual so as to let the Game use the GameState manager to call a consistent function.
*/
class GameState
{
public:
	/*The States KeyBoard and Mouse Handling Function*/
	virtual void HandleInput() = 0;
	/*The States Logic Update Function*/
	virtual void Update(float dt) = 0;
	/*The States Draw Function*/
	virtual void Draw(float dt, sf::RenderWindow& wnd) = 0;

};

