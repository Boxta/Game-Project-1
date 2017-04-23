#pragma once
#include <SFML\Graphics.hpp>
#include "CmnTextureStore.h"

class UIButton
{
public:
	UIButton(CmnTextureStore& str);
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
	void Initiate(int x, int y);

	/*The States Draw Function*/
	void Draw(sf::RenderWindow& wnd);

private:
	/*Common Texture Store Reference*/
	CmnTextureStore& mCmnStore;

	/*The Buttons Sprite*/
	sf::Sprite mButtonSprite;

	/*Size Should Equal Pixel Image Size Of Button*/
	const int mWidth = 250;
	const int mHeight = 80;

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
};

