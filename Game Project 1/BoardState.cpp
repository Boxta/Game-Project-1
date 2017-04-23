#include "BoardState.h"
#include "Game.h"


void BoardState::Initiate()
{
	/*Only Initiate Once*/
	if (mInitiated)
		return;
	else
		mInitiated = true;

	/*Setup Sprite*/
	mBackgroundImage.setTexture(mCommonStore.GetTextureRef("BoardBackground"));
	mBackgroundImage.setPosition(0.0f, 0.0f);
}

void BoardState::HandleInput()
{
}

void BoardState::Update(float dt)
{
}

void BoardState::Draw()
{
	mWindow.clear();
	mWindow.draw(mBackgroundImage);
}

void BoardState::HandleEvents(sf::Event & ev)
{
}

BoardState::BoardState(StateManager& stmgr,
	sf::RenderWindow& wnd)
	:
	mBackgroundImage(),
	mBackgroundFill(),
	mStateManager(stmgr),
	mCommonStore(stmgr.mGameReference.mCommonStore),
	mWindow(wnd)
{
	mBackgroundFill.setFillColor(sf::Color::Black);
	mBackgroundFill.setSize(sf::Vector2f(1920, 1080));
	mBackgroundFill.setPosition(sf::Vector2f(0, 0));
}


BoardState::~BoardState()
{
}
