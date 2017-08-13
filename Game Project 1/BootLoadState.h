#pragma once
#include "GameState.h"
#include <SFML\Graphics.hpp>
#include "CmnStore.h"
#include <thread>

class BootLoadState :
	public GameState
{
public:
	/*Initiate Variables and Structures*/
	virtual void Initiate();
	/*The States Keyboard and Mouse Handling Function*/
	virtual void HandleInput();
	/*The States Logic Update Function*/
	virtual void Update(float dt);
	/*The States Draw Function*/
	virtual void Draw();
	/*Handle Events*/
	virtual void HandleEvents(sf::Event& ev);
private:
	sf::Sprite mBootImage;
	void LoadCommonStoreAssets();
	Game& mGameReference;
public:
	BootLoadState(Game& ref);
	~BootLoadState();
};

