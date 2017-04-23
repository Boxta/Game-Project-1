#pragma once
#include "GameState.h"
#include <SFML\Audio.hpp>
#include "UIButton.h"
#include <SFML\Window.hpp>

class MainMenu :
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
	sf::Sprite mBackgroundImage;
	sf::Text mText1;
	sf::Font mFont1;
	sf::Music mMenuMusic;
	bool mMusicIsPlaying = false;
	UIButton mStartGame_Button;
	UIButton mLoadGame_Button;
	UIButton mTutorialGame_Button;
public:
	MainMenu(StateManager& stmgr,
		CmnTextureStore& str,
		sf::RenderWindow& wnd);
	~MainMenu();
};

