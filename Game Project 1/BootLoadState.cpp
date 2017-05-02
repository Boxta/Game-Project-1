#include "BootLoadState.h"
#include "Game.h"

void BootLoadState::Initiate()
{
	/*Load Common Textures*/
	mGameReference.GetCommonStore().AddTexture("MenuBackground", "Media\\Background2.png");
	mGameReference.GetCommonStore().AddTexture("BoardBackground", "Media\\Background1.png");
	mGameReference.GetCommonStore().AddTexture("BootLoadImage", "Media\\LoadingIcon.png");
	mGameReference.GetCommonStore().AddTexture("BaseButtons", "Media\\BaseButtons.png");
	mGameReference.GetCommonStore().AddTexture("EnemyPicture", "Media\\EnemyPortrait.png");
	mGameReference.GetCommonStore().AddTexture("PlayerPicture", "Media\\PlayerPortrait.png");
	mGameReference.GetCommonStore().AddTexture("TestCard", "Media\\TestCard0.png");
	mGameReference.GetCommonStore().AddTexture("SelectBoarder", "Media\\BoardSelect.png");
	mGameReference.GetCommonStore().AddTexture("Logo", "Media\\Logo1.png");
	/*Load Common Fonts*/
	mGameReference.GetCommonStore().AddFont("System", "Media/font1.ttf");

	/*Only Initiate Once*/
	if (mInitiated)
		return;
	else
		mInitiated = true;

	/*Setup Text*/
	mText1.setFont(mGameReference.GetCommonStore().GetFontRef("System"));
	mText1.setString("Loading Assets..");
	mText1.setCharacterSize(24);
	mText1.setPosition(sf::Vector2f(1920 / 2 - 100, 1080 / 2 - 300));

	/*Setup Sprites*/
	mCompanyIcon.setTexture(mGameReference.GetCommonStore().GetTextureRef("BootLoadImage"));
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
