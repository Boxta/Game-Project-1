#pragma once
#include "GameState.h"
#include <SFML\Graphics.hpp>
#include "CmnTextureStore.h"


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
	sf::RenderWindow& mWindow;
	StateManager& mStateManager;
	CmnTextureStore& mCommonTextureStore;
	sf::RectangleShape mBackgroundFill;
	sf::Sprite mCompanyIcon;
	sf::Text mText1;
	sf::Font mFont1;
	const float mWaitTime = 2.0f;
	float mWaitTimer = 0.0f;
	bool mInitiated = false;
public:
	BootLoadState(StateManager& stmgr,
		sf::RenderWindow& wnd);
	~BootLoadState();
};

