#pragma once
#include "GameState.h"
class BoardState :
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

	BoardState(StateManager& stmgr,
		CmnTextureStore& str,
		sf::RenderWindow& wnd);
	~BoardState();

private:
	sf::RenderWindow& mWindow;
	StateManager& mStateManager;
	CmnTextureStore& mCommonTextureStore;
	sf::RectangleShape mBackgroundFill;
	sf::Sprite mBackgroundImage;
};

