#pragma once
#include "GameState.h"
#include "CmnTextureStore.h"
#include "AnimatedSprite.h"
#include <chrono>

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
	AnimatedSprite AniSprite;
	sf::CircleShape mShape;
	sf::Sprite mMario;
	CmnTextureStore mCommonTextureStore;
};

