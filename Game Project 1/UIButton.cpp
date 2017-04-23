#include "UIButton.h"



UIButton::UIButton(CmnTextureStore& str)
	:
	mCmnStore(str)
{
	
}


UIButton::~UIButton()
{
}

bool UIButton::CheckIfClicked(int xpos, int ypos)
{
	return mRectangle.contains(xpos, ypos);
}

void UIButton::Initiate(int x, int y, sf::String txt)
{
	/*Setup Fonts*/
	mFont1.loadFromFile("Media/font1.ttf");
	
	/*Set Initial Position*/
	mXPosition = x;
	mYPosition = y;

	/*Set Text*/
	mText1.setString(txt);
	mText1.setFont(mFont1);
	mText1.setPosition(
		sf::Vector2f((float(mXPosition) + (WIDTH / 2) - 
			(mText1.getString().getSize() * 8)),
		(float(mYPosition) + HEIGHT / 2) - 16));
	mText1.setColor(sf::Color::Black);
	mText1.setStyle(mText1.Bold);

	/*Set Initial Texture Rectangle*/
	mTextureRectangle.left = mTextureXPosition * WIDTH;
	mTextureRectangle.top = mTextureYPosition * HEIGHT;
	mTextureRectangle.width = WIDTH;
	mTextureRectangle.height = HEIGHT;

	/*Set Initial Screen Rectangle*/
	mRectangle.left = mXPosition;
	mRectangle.top = mYPosition;
	mRectangle.width = WIDTH;
	mRectangle.height = HEIGHT;

	/*Setup Button Sprite Using Initial Rectangles*/
	mButtonSprite.setTexture(mCmnStore.GetTextureRef("BaseButtons"));
	mButtonSprite.setTextureRect(mTextureRectangle);
	mButtonSprite.setPosition(float(mXPosition), float(mYPosition));

}

void UIButton::Draw(sf::RenderWindow & wnd)
{
	if (mIsPressed)
	{
		mButtonSprite.setColor(sf::Color::Red);
		wnd.draw(mButtonSprite);
	}
	else
	{
		mButtonSprite.setColor(sf::Color::White);
		wnd.draw(mButtonSprite);
	}
	wnd.draw(mText1);
}
