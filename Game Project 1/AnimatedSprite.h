#pragma once
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <vector>

class AnimatedSprite :
	public sf::Sprite
{
public:
	class Animation
	{
	public:

		int mStartFrame;
		int mEndFrame;

		float mDuration;

		Animation(int startFrame, int endFrame, float duration)
		{
			mStartFrame = startFrame;
			mEndFrame = endFrame;
			mDuration = duration;
		}

		int getLength() { return mEndFrame - mStartFrame + 1; }
	};
public:

	AnimatedSprite();
	AnimatedSprite(sf::Texture& texture, 
		int width, int height, 
		int x, int y, 
		std::vector<Animation>& animations);
	~AnimatedSprite();

	void Initiate(const int startanimation, const int frame);
	void Update(const float dt);
	void Draw(sf::RenderWindow& wnd);

	const auto& GetPosition()
	{
		return sf::Vector2<int>(mXPosition, mYPosition);
	}

	void setAnimation(bool val)
	{
		mIsAnimating = val;
	}

	void setPosition(sf::Vector2<int> pos);

	/*Animated Sprites Sprite*/
	Sprite mSprite;
private:


	/*Sprite and Sprite Animation Frame Position*/
	int mXPosition;
	int mYPosition;

	/*Current Frame In Use*/
	int mCurrentFrame;

	/*Sprite Width and Height*/
	int mWidth;
	int mHeight;

	/*Animation On/Off Toggle*/
	bool mIsAnimating = true;

	/* Array of Animations */
	std::vector<Animation> mAnimationList;

	/* Current Animation Being Used */
	unsigned int mCurrentAnimation;

	/* Time Counter */
	float mTimeCounter;

};

