#include "UIButton.h"

UIButton::UIButton(CmnStore& str)
	:
	mCmnStore(str)
{
}


UIButton::~UIButton()
{
	delete mAnimatedSprite;
}

bool UIButton::CheckIfClicked(int xpos, int ypos)
{
	return mRectangle.contains(xpos, ypos);
}

void UIButton::Initiate(int x, int y, 
	sf::String txt, 
	int textSize,
	sf::String texName,
	const int frameCount,
	const int frameWidth,
	const int frameHeight)
{
	/*Set Text*/
	mText1.setString(txt);
	mText1.setFont(mCmnStore.GetFontRef("System"));
	mText1.setStyle(mText1.Bold);
	mText1.setCharacterSize(textSize);
	mText1.setPosition((x + (frameWidth / 2)) - (mText1.getLocalBounds().width / 2), 
		(y + (frameHeight / 2)) - (mText1.getLocalBounds().height));

	/*Set Click Rectangle*/
	mRectangle.left = x;
	mRectangle.top = y;
	mRectangle.width = frameWidth;
	mRectangle.height = frameHeight;

	/*Animation*/
	AnimatedSprite::Animation Animation1 = { 0 , frameCount - 1, 0.5f };
	std::vector<AnimatedSprite::Animation> mAnimations;
	mAnimations.push_back(Animation1);

	/*Setup Animated Sprite*/
	mAnimatedSprite = new AnimatedSprite( mCmnStore.GetTextureRef(texName),
		frameWidth, frameHeight, x, y, mAnimations, 0, 0);
}

void UIButton::Update(float dt)
{
	mAnimatedSprite->Update(dt);
}

void UIButton::Draw(sf::RenderWindow & wnd)
{
	mAnimatedSprite->Draw(wnd);
	wnd.draw(mText1);
}

void UIButton::AnimationToggle(bool val)
{
	mAnimatedSprite->setAnimation(val);
}
