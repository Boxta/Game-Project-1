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
	AnimatedSprite(sf::Texture& texture, int width, 
		int height, int x, int y, std::vector<Animation>& animations);
	~AnimatedSprite();

	void Initiate();
	void Update(const float dt);
	void Draw(sf::RenderWindow& wnd);

	auto& GetPosition()
	{
		return sf::Vector2<int>(mXPosition, mYPosition);
	}

	void setPosition(sf::Vector2<int> pos);


private:
	Sprite mSprite;
	int mXPosition;
	int mYPosition;
	int mCurrentFrame;
	int mWidth;
	int mHeight;

	/* Array of Animations */
	std::vector<Animation> mAnimationList;

	/* Current Animation Being Used */
	unsigned int mCurrentAnimation;

	/* Time Counter */
	float mTimeCounter;

};

