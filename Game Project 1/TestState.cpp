#include "TestState.h"

TestState::TestState()
	:
	mShape(300.0f),
	AniSprite()
{
	mShape.setFillColor(sf::Color::Green);
}

TestState::~TestState()
{
}

void TestState::Initiate(CmnTextureStore& str)
{
	mCommonTextureStore = str;
	mMario.setTexture(mCommonTextureStore.GetTextureRef("Test"));
	mMario.setPosition(100.0f, 100.0f);
	AniSprite = { mCommonTextureStore.GetTextureRef("AnimatedBox") , 64, 64, 0, 0 };
	
	AniSprite.Initiate();
}

void TestState::HandleInput()
{
}

void TestState::Update(float dt)
{
	AniSprite.Update(dt);
}

void TestState::Draw(float dt, sf::RenderWindow& wnd)
{
	//Clear the window before drawing
	wnd.clear();
	//Draw the shape to the cleared window
	//wnd.draw(mShape);
	//wnd.draw(mMario);
	AniSprite.Draw(wnd);
}
