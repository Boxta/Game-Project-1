#include "BootLoadState.h"

void BootLoadState::Initiate()
{
	/*Setup Fonts*/
	mFont1.loadFromFile("Media/font1.ttf");
	mText1.setFont(mFont1);
	mText1.setString("Loading Assets..");
	mText1.setCharacterSize(24);
	mText1.setPosition(sf::Vector2f(1920 / 2 - 100, 1080 / 2 - 300));

	/*Setup Sprites*/
	mCompanyIcon.setTexture(mCommonTextureStore.GetTextureRef("BootLoadImage"));
	mCompanyIcon.setPosition(sf::Vector2f(1920 / 2 - 170, 1080 / 2 - 250));
}

void BootLoadState::HandleInput()
{
}

void BootLoadState::Update(float dt)
{
	mWaitTimer += dt;
	if (mWaitTimer > mWaitTime)
	{
		/*Reset Timer*/
		mWaitTimer = 0;

		/*Call Next State*/
		mStateManager.PopState();
	}
}

void BootLoadState::Draw()
{
	mWindow.clear();
	mWindow.draw(mBackgroundFill);
	mWindow.draw(mCompanyIcon);
	mWindow.draw(mText1);
}

void BootLoadState::HandleEvents(sf::Event& ev)
{
}

BootLoadState::BootLoadState(StateManager& stmgr,
	CmnTextureStore& str,
	sf::RenderWindow& wnd)
	:
	mBackgroundFill(),
	mCompanyIcon(),
	mStateManager(stmgr),
	mCommonTextureStore(str),
	mWindow(wnd)
{
	mBackgroundFill.setFillColor(sf::Color::Black);
	mBackgroundFill.setSize(sf::Vector2f(1920, 1080));
	mBackgroundFill.setPosition(sf::Vector2f(0, 0));
}


BootLoadState::~BootLoadState()
{
}
