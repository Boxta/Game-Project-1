#include "BoardState.h"



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
	CmnTextureStore& str,
	sf::RenderWindow& wnd)
	:
	mStateManager(stmgr),
	mCommonTextureStore(str),
	mWindow(wnd)
{
}


BoardState::~BoardState()
{
}
