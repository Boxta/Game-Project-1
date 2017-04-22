#include "TestState.h"

TestState::TestState()
	:
	mShape(300.0f),
	mTileManager(),
	View1(sf::FloatRect(camerax, cameray, 800, 600))
{
	mShape.setFillColor(sf::Color::White);
}

TestState::~TestState()
{
}

void TestState::Initiate(CmnTextureStore& str)
{
	/*Setup Font*/
	SF_Font.loadFromFile("Media/font1.ttf");
	SF_Text.setFont(SF_Font);
	SF_Text.setString("ABCDEFGHIJKLMNOPQRSTUVWXYZ\nabcdefghijklmnopqrstuvwxyz\n0123456789");
	SF_Text.setCharacterSize(70);

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
		Sheet2Animations, "TileSheet2", str, false, 1, 0));

}

void TestState::HandleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		UpdateCameraPosition(-1, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		UpdateCameraPosition(1, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		UpdateCameraPosition(0, -1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		UpdateCameraPosition(0, 1);
	}
}

void TestState::UpdateCameraPosition(int x, int y)
{
	View1.setCenter(View1.getCenter().x + x, View1.getCenter().y + y);
}

void TestState::Update(float dt)
{
	mTileManager.Update(dt);
}

void TestState::Draw(float dt, sf::RenderWindow& wnd)
{
	/*Set View*/
	wnd.setView(View1);

	/*Clear Window*/
	wnd.clear();

	/*Draw Shape*/
	wnd.draw(mShape);
	
	/*Draw Tiles*/
	mTileManager.Draw(wnd);

	/*Draw Text*/
	wnd.draw(SF_Text);
}
