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
	std::vector<AnimatedSprite::Animation> Sheet1Animations;
	Sheet1Animations.push_back(AnimatedSprite::Animation(0, 8, 0.1f));
	Sheet1Animations.push_back(AnimatedSprite::Animation(0, 8, 0.1f));
	Sheet1Animations.push_back(AnimatedSprite::Animation(0, 8, 0.1f));
	Sheet1Animations.push_back(AnimatedSprite::Animation(0, 8, 0.1f));
	std::vector<AnimatedSprite::Animation> Sheet2Animations;
	Sheet2Animations.push_back(AnimatedSprite::Animation(0, 5, 1.05f));
	Sheet2Animations.push_back(AnimatedSprite::Animation(0, 5, 1.05f));
	Sheet2Animations.push_back(AnimatedSprite::Animation(0, 5, 1.05f));

	mTileManager.AddTileLayer(0, mTileManager.CreateLayerTiles(50, 50, 64, 64,
		Sheet2Animations, "TileSheet2", str, true, 0, 0));
	mTileManager.AddTileLayer(1, mTileManager.CreateLayerTiles(50, 50, 64, 64,
		Sheet2Animations, "TileSheet2", str, true, 1, 0));

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
