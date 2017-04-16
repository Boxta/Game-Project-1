#include "TestState.h"

TestState::TestState()
	:
	mShape(300.0f),
	mTileManager()
{
	mShape.setFillColor(sf::Color::White);
}

TestState::~TestState()
{
}

void TestState::Initiate(CmnTextureStore& str)
{
	/*Setup a Layer Of Animated Tiles and Tile Manager*/
	std::vector<AnimatedSprite::Animation> tempaniamtions;
	tempaniamtions.push_back(AnimatedSprite::Animation(0, 8, 0.1f));
	tempaniamtions.push_back(AnimatedSprite::Animation(0, 8, 0.1f));
	tempaniamtions.push_back(AnimatedSprite::Animation(0, 8, 0.1f));
	tempaniamtions.push_back(AnimatedSprite::Animation(0, 8, 0.1f));
	mTileManager.AddTileLayer(0, mTileManager.CreateLayerTiles(10, 10, 64, 64,
		tempaniamtions, "TileSheet2", str));
	mTileManager.AddTileLayer(1, mTileManager.CreateLayerTiles(5, 5, 64, 64,
		tempaniamtions, "TileSheet1", str));
	mTileManager.Initiate(str);
}

void TestState::HandleInput()
{
}

void TestState::Update(float dt)
{
	mTileManager.Update(dt);
}

void TestState::Draw(float dt, sf::RenderWindow& wnd)
{
	/*Clear Window*/
	wnd.clear();

	/*Draw Shape*/
	wnd.draw(mShape);
	
	/*Draw Tiles*/
	mTileManager.Draw(wnd);
}
