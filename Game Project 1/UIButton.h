#pragma once
#include <SFML\Graphics.hpp>
#include "CmnStore.h"

class UIButton
{
public:
	UIButton(CmnStore& str);
	~UIButton();

	/*Return Rectangle Reference*/
	sf::IntRect& GetRectangle() { return mRectangle; }

	/*Return If Passed Position Insigth Rectangle*/
	bool CheckIfClicked(int xpos, int ypos);

	/*Return Pressed State*/
	bool GetPressedState() { return mIsPressed; }

	/*Set Pressed State*/
	void SetPressedState(bool to) { mIsPressed = to; }

	/*Initiate Button*/
	void Initiate(int x, int y, sf::String txt);

	/*The States Draw Function*/
	void Draw(sf::RenderWindow& wnd);

	/*Size Should Equal Pixel Image Size Of Button*/
	static const int WIDTH = 250;
	static const int HEIGHT = 80;

private:
	/*Common Texture Store Reference*/
	CmnStore& mCmnStore;

	/*The Buttons Sprite*/
	sf::Sprite mButtonSprite;

	/*Pixel Position In Screen Space*/
	int mXPosition = 0;
	int mYPosition = 0;

	/*Button Screen Rectangle*/
	sf::IntRect mRectangle;

	/*Texture Position In Image Coordinates*/
	int mTextureXPosition = 0;
	int mTextureYPosition = 0;

	/*Button Texture Rectangle*/
	sf::IntRect mTextureRectangle;

	/*Track Button Pressed State*/
	bool mIsPressed = false;

	/*Text*/
	sf::String mString1;
	sf::Text mText1;
};

