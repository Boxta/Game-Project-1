#include "BootLoadState.h"
#include "Game.h"

void BootLoadState::Initiate()
{
	mGameReference.GetCommonStore().AddTexture("BootLoadImage", "Media\\LoadingIcon.png");
	mBootImage.setTexture(mGameReference.GetCommonStore().GetTextureRef("BootLoadImage"));
	mBootImage.setPosition(sf::Vector2f(100.0f, 100.0f));
	/*Add Assets To Common Store*/
	std::thread LoadThread(&BootLoadState::LoadCommonStoreAssets, this);
	LoadThread.join(); 
}

void BootLoadState::HandleInput()
{
}

void BootLoadState::Update(float dt)
{
	mBootImage.setPosition(sf::Vector2f(mBootImage.getPosition().x + 30.0f, 100.0f));
}

void BootLoadState::Draw()
{
	mGameReference.GetWindow().draw(mBootImage);
}

void BootLoadState::HandleEvents(sf::Event& ev)
{
}

void BootLoadState::LoadCommonStoreAssets()
{
	/*Add Common Store Assets*/
	mGameReference.GetCommonStore().AddTexture("MenuBackground", "Media\\Background2.png");
	mGameReference.GetCommonStore().AddTexture("BoardBackground", "Media\\Background1.png");
	mGameReference.GetCommonStore().AddTexture("BaseButtons", "Media\\BaseButtons.png");
	mGameReference.GetCommonStore().AddTexture("EnemyPicture", "Media\\EnemyPortrait.png");
	mGameReference.GetCommonStore().AddTexture("PlayerPicture", "Media\\PlayerPortrait.png");
	mGameReference.GetCommonStore().AddTexture("TestCard", "Media\\Cards.png");
	mGameReference.GetCommonStore().AddTexture("SelectBoarder", "Media\\BoardSelect.png");
	mGameReference.GetCommonStore().AddTexture("Logo", "Media\\Logo1.png");
	mGameReference.GetCommonStore().AddTexture("CardBack", "Media\\CardBack.png");
	mGameReference.GetCommonStore().AddTexture("DrawButtons", "Media\\DrawButtons.png");
	mGameReference.GetCommonStore().AddTexture("TurnIcons", "Media\\TurnIcons.png");

	/*Load Common Fonts*/
	mGameReference.GetCommonStore().AddFont("System", "Media/MainFont.ttf");

	/*Change to Main Menu State*/
	mGameReference.ChangeGameState(mGameReference.GetState_MainMenu());
}

BootLoadState::BootLoadState(Game& ref)
	:
	mGameReference(ref)
{
}


BootLoadState::~BootLoadState()
{
}
