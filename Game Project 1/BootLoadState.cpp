#include "BootLoadState.h"



void BootLoadState::Initiate(CmnTextureStore & str)
{
	/*Setup Font*/
	mFont1.loadFromFile("Media/font1.ttf");
	mText1.setFont(mFont1);
	mText1.setString("Loading Assets..");
	mText1.setCharacterSize(24);
	mText1.setPosition(sf::Vector2f(1920 / 2 - 100, 1080 / 2 - 300));

	/*Setup Sprites*/
	mCompanyIcon.setTexture(str.GetTextureRef("BootLoadImage"));
	mCompanyIcon.setPosition(sf::Vector2f(1920 / 2 - 170, 1080 / 2 - 250));
}

void BootLoadState::HandleInput()
{
}

void BootLoadState::Update(float dt)
{
}

void BootLoadState::Draw(float dt, sf::RenderWindow & wnd)
{
	wnd.clear();
	wnd.draw(mBackgroundFill);
	wnd.draw(mCompanyIcon);
	wnd.draw(mText1);
}

BootLoadState::BootLoadState()
	:
	mBackgroundFill(),
	mCompanyIcon()
{
	mBackgroundFill.setFillColor(sf::Color::Black);
	mBackgroundFill.setSize(sf::Vector2f(1920, 1080));
	mBackgroundFill.setPosition(sf::Vector2f(0, 0));
}


BootLoadState::~BootLoadState()
{
}
