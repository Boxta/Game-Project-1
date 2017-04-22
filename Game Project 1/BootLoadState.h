#pragma once
#include "GameState.h"
#include <SFML\Graphics.hpp>
#include "CmnTextureStore.h"


class BootLoadState :
	public GameState
{
public:
	/*Initiate Variables and Structures*/
	virtual void Initiate(CmnTextureStore& str);
	/*The States Keyboard and Mouse Handling Function*/
	virtual void HandleInput();
	/*The States Logic Update Function*/
	virtual void Update(float dt);
	/*The States Draw Function*/
	virtual void Draw(float dt, sf::RenderWindow& wnd);

	CmnTextureStore mCommonTextureStore;
	sf::RectangleShape mBackgroundFill;
	sf::Sprite mCompanyIcon;
	sf::Text mText1;
	sf::Font mFont1;
	unsigned int mAssetLoadCounter = 0;
	BootLoadState();
	~BootLoadState();
};

