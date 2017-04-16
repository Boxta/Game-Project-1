#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite()
	:
	mSprite(),
	mWidth(0),
	mHeight(0)
{
}

AnimatedSprite::AnimatedSprite(sf::Texture& texture,
	int width, int height, int x, int y, std::vector<Animation>& animations)
	:
	mSprite(texture, sf::IntRect(x, y, width, height)),
	mWidth(width),
	mHeight(height), 
	mXPosition(x),
	mYPosition(y),
	mAnimationList(animations)
{}


AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::Initiate(const int Animation, const int frame)
{
	mSprite.setPosition(mXPosition, mYPosition);
	mCurrentAnimation = Animation;
	mCurrentFrame = frame;
	mTimeCounter = 0.0f;
	mSprite.setTextureRect(sf::IntRect(mCurrentFrame * mWidth, mCurrentAnimation * mHeight, mWidth, mHeight));
}

void AnimatedSprite::Update(const float dt)
{
	/*Only Update If Not Animating*/
	if (!mIsAnimating)
		return;

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

void AnimatedSprite::Draw(sf::RenderWindow& wnd)
{
	wnd.draw(mSprite);
}

void AnimatedSprite::setPosition(sf::Vector2<int> pos)
{
	mXPosition = pos.x;
	mXPosition = pos.y;
}
