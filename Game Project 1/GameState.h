#pragma once

#include <stack>
#include <SFML/Graphics.hpp>

/*
Virtual so as to let the Game use the GameState manager to call a consistent function.
*/
class GameState
{
public:
	virtual void Draw(float dt, sf::RenderWindow& wnd) = 0;
	virtual void Update(float dt) = 0;
	virtual void HandleInput() = 0;
};

