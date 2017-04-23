#include "BoardState.h"
#include "Game.h"


void BoardState::Initiate()
{
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
}

void BoardState::HandleEvents(sf::Event & ev)
{
}

BoardState::BoardState(StateManager& stmgr,
	sf::RenderWindow& wnd)
	:
	mStateManager(stmgr),
	mCommonTextureStore(stmgr.mGameReference.mCommonTextureStore),
	mWindow(wnd)
{
}


BoardState::~BoardState()
{
}
