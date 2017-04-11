#pragma once
#include "GameState.h"

class TestState :
	public GameState
{
public:
	TestState();
	~TestState();
	
	virtual void Draw(float dt, sf::RenderWindow& wnd);
	virtual void Update(float dt);
	virtual void HandleInput();

	//Create a SFML Circle shape passing in the radius
	sf::CircleShape shape;
};

