#pragma once
#include "GameState.h"
#include "CmnTextureStore.h"
#include "AnimatedSprite.h"
#include <chrono>
#include "AnimatedSprite.h"
#include <vector>
#include "TileManager.h"

class TestState 
	:
	public GameState
{
public:

	TestState();
	~TestState();
	virtual void Initiate(CmnTextureStore& str);
	virtual void Draw(float dt, sf::RenderWindow& wnd);
	virtual void Update(float dt);
	virtual void HandleInput();

	//Create a SFML Circle shape passing in the radius
	
	sf::CircleShape mShape;

	CmnTextureStore mCommonTextureStore;

	TileManager mTileManager;

	void UpdateCameraPosition(int x, int y);

	sf::Text SF_Text;
	sf::Font SF_Font;
	int camerax = 0;
	int cameray = 0;
	sf::View View1;

};

