#pragma once
#include <SFML\Graphics.hpp>
#include "CmnStore.h"
#include "AnimatedSprite.h"

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
	void Initiate(int x, int y,
		sf::String txt,
		int textSize,
		sf::String texName,
		const int frameCount,
		const int frameWidth,
		const int frameHeight);

	/*Update Sprite*/
	void Update(float dt);

	/*The States Draw Function*/
	void Draw(sf::RenderWindow& wnd);

	/*Frame Size*/
	int mWidth = 250;
	int mHeight = 80;

	/*Toggle Animation*/
	void AnimationToggle(bool val);

private:
	/*Common Texture Store Reference*/
	CmnStore& mCmnStore;

	/*The Buttons Sprite*/
	sf::Sprite mButtonSprite;

	/*Button Screen Rectangle*/
	sf::IntRect mRectangle;

	/*Track Button Pressed State*/
	bool mIsPressed = false;

	/*Text*/
	sf::String mString1;
	sf::Text mText1;

	/*Frame Count*/
	int mFrameCount = 0;

	/*Animated Sprite*/
	AnimatedSprite *mAnimatedSprite = nullptr;
};

