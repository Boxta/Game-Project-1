#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite()
	:
	mSprite(),
	Animation1(0, 8, 0.05f),
	Animation2(0, 8, 0.05f),
	Animation3(0, 8, 0.05f),
	Animation4(0, 8, 0.05f),
	mWidth(0),
	mHeight(0)
{
}

AnimatedSprite::AnimatedSprite(sf::Texture& texture,
	int width, int height, int x, int y)
	:
	mSprite(texture, sf::IntRect(x, y, width, height)),
	Animation1(0, 8, 0.05f),
	Animation2(0, 8, 0.05f),
	Animation3(0, 8, 0.05f),
	Animation4(0, 8, 0.05f),
	mWidth(width),
	mHeight(height)
{
}


AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::Initiate()
{
	mAnimationList.push_back(Animation1);
	mAnimationList.push_back(Animation2);
	mAnimationList.push_back(Animation3);
	mAnimationList.push_back(Animation4);
	mCurrentAnimation = 3;
	mCurrentFrame = 0;
	mTimeCounter = 0.0f;
}

void AnimatedSprite::Update(const float dt)
{
	/*Only Update If Animation Present*/
	if (mCurrentAnimation < 0 ||
		mCurrentAnimation > mAnimationList.size())
		return;

	const float Duration = mAnimationList[mCurrentAnimation].mDuration;
	const int MaxFrames = mAnimationList[mCurrentAnimation].getLength();
	
	/*Update mTimeCounter*/
	mTimeCounter += dt;

	if (mTimeCounter > Duration)
	{
		mTimeCounter = 0;

		/*Increment The CurrentFrame unless on the Max Frame 
		in which case loop back to frame 0*/
		if (mCurrentFrame == (MaxFrames - 1))
			mCurrentFrame = 0;
		else
			mCurrentFrame++;

		/*Build New Texture Rectangle For Sprite*/
		sf::IntRect TempRectangle = mSprite.getTextureRect();
		TempRectangle.left = TempRectangle.width * mCurrentFrame;
		TempRectangle.top = TempRectangle.height * mCurrentAnimation;

		/*Update Sprite Texture Rectangle*/
		mSprite.setTextureRect(TempRectangle);
	}
}

void AnimatedSprite::Draw(sf::RenderWindow & wnd)
{
	wnd.draw(mSprite);
}
