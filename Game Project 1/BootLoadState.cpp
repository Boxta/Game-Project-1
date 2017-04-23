#include "BootLoadState.h"
#include "Game.h"

void BootLoadState::Initiate()
{
	/*Only Initiate Once*/
	if (mInitiated)
		return;
	else
		mInitiated = true;

	/*Setup Text*/
	mText1.setFont(mCommonStore.GetFontRef("System"));
	mText1.setString("Loading Assets..");
	mText1.setCharacterSize(24);
	mText1.setPosition(sf::Vector2f(1920 / 2 - 100, 1080 / 2 - 300));

	/*Setup Sprites*/
	mCompanyIcon.setTexture(mCommonStore.GetTextureRef("BootLoadImage"));
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
		mStateManager.mGameReference.ChangeGameState(mStateManager.mGameReference.mState_MainMenu);
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
	sf::RenderWindow& wnd)
	:
	mBackgroundFill(),
	mCompanyIcon(),
	mStateManager(stmgr),
	mCommonStore(stmgr.mGameReference.mCommonStore),
	mWindow(wnd)
{
	mBackgroundFill.setFillColor(sf::Color::Black);
	mBackgroundFill.setSize(sf::Vector2f(1920, 1080));
	mBackgroundFill.setPosition(sf::Vector2f(0, 0));
}


BootLoadState::~BootLoadState()
{
}
