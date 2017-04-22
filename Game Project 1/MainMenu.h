#pragma once
#include "GameState.h"
class MainMenu :
	public GameState
{
public:
	/*Initiate Variables and Structures*/
	virtual void Initiate(CmnTextureStore& str,
		StateManager& stmgr);
	/*The States Keyboard and Mouse Handling Function*/
	virtual void HandleInput();
	/*The States Logic Update Function*/
	virtual void Update(float dt);
	/*The States Draw Function*/
	virtual void Draw(float dt, sf::RenderWindow& wnd);

	CmnTextureStore mCommonTextureStore;
	sf::RectangleShape mBackgroundFill;
	sf::Text mText1;
	sf::Font mFont1;

	MainMenu();
	~MainMenu();
};

