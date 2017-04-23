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

void UIButton::Initiate(int x, int y)
{
	/*Set Initial Position*/
	mXPosition = x;
	mYPosition = y;

	/*Set Initial Texture Rectangle*/
	mTextureRectangle.left = mTextureXPosition * mWidth;
	mTextureRectangle.top = mTextureYPosition * mHeight;
	mTextureRectangle.width = mWidth;
	mTextureRectangle.height = mHeight;

	/*Set Initial Screen Rectangle*/
	mRectangle.left = mXPosition;
	mRectangle.top = mYPosition;
	mRectangle.width = mWidth;
	mRectangle.height = mHeight;

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
}
