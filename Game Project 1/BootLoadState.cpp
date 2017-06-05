#include "BootLoadState.h"
#include "Game.h"

void BootLoadState::Initiate()
{
	/*Setup Text*/
	mText1.setFont(mGameReference.GetCommonStore().GetFontRef("System"));
	mText1.setString("Loading Assets..");
	mText1.setCharacterSize(24);
	mText1.setPosition(sf::Vector2f(mGameReference.GetWindow().getSize().x / 2 - 100, mGameReference.GetWindow().getSize().y / 2 - 300));
	
	/*Setup Sprites*/
	mCompanyIcon.setTexture(mGameReference.GetCommonStore().GetTextureRef("BootLoadImage"));
	mCompanyIcon.setPosition(sf::Vector2f(mGameReference.GetWindow().getSize().x / 2 - 170, mGameReference.GetWindow().getSize().y / 2 - 250));
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
		mGameReference.ChangeGameState(mGameReference.GetState_MainMenu());
	}
}

void BootLoadState::Draw()
{
	mGameReference.GetWindow().clear();
	mGameReference.GetWindow().draw(mBackgroundFill);
	mGameReference.GetWindow().draw(mCompanyIcon);
	mGameReference.GetWindow().draw(mText1);
}

void BootLoadState::HandleEvents(sf::Event& ev)
{
}

BootLoadState::BootLoadState(Game& ref)
	:
	mBackgroundFill(),
	mCompanyIcon(),
	mGameReference(ref)
{
	mBackgroundFill.setFillColor(sf::Color::Black);
	mBackgroundFill.setSize(sf::Vector2f(1920, 1080));
	mBackgroundFill.setPosition(sf::Vector2f(0, 0));
}


BootLoadState::~BootLoadState()
{
}
