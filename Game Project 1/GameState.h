#pragma once

#include <stack>
#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>
#include "CmnStore.h"
#include "StateManager.h"

/*
Virtual so as to let the Game use the GameState manager to call a consistent function.
*/
class GameState
{
public:
	/*Initiate Variables and Structures*/
	virtual void Initiate() = 0;
	/*The States Keyboard and Mouse Handling Function*/
	virtual void HandleInput() = 0;
	/*The States Logic Update Function*/
	virtual void Update(float dt) = 0;
	/*The States Draw Function*/
	virtual void Draw() = 0;
	/*Handle Events*/
	virtual void HandleEvents(sf::Event& ev) = 0;

};

