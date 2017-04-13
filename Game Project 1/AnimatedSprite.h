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
	Sprite mSprite;
	AnimatedSprite();
	AnimatedSprite(sf::Texture& texture, int width, 
		int height, int x, int y);
	~AnimatedSprite();

	void Initiate();
	void Update(const float dt);
	void Draw(sf::RenderWindow& wnd);


private:
	Animation Animation1;
	Animation Animation2;
	Animation Animation3;
	Animation Animation4;

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

