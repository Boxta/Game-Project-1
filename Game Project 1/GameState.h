#pragma once

#include <stack>
#include "StateManager.h"
#include <SFML/Graphics.hpp>

class GameState
{
public:
	StateManager* mManager = nullptr;
	virtual void Draw(float dt, sf::RenderWindow& wnd) = 0;
	virtual void Update(float dt) = 0;
	virtual void HandleInput() = 0;
};

