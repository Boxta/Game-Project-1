#include "BoardState.h"
#include "Game.h"


void BoardState::Initiate()
{
	/*Only Initiate Once*/
	if (mInitiated)
		return;
	else
		mInitiated = true;

	/*Setup Enemy*/
	mEnemy.Initiate(1620.0f, 700.0f, "Donald Trump", 1703.0f, 721.0f);
	
	/*Setup Text*/
	mPlayerScoreText.setFont(mGameReference.GetCommonStore().GetFontRef("System"));
	mPlayerScoreText.setString(std::to_string(mPlayerScore));
	mPlayerScoreText.setPosition(360.0f, 610.0f);
	mPlayerScoreText.setFillColor(sf::Color::Black);
	mPlayerScoreText.setCharacterSize(200);

	mEnemyScoreText.setFont(mGameReference.GetCommonStore().GetFontRef("System"));
	mEnemyScoreText.setString(std::to_string(mEnemyScore));
	mEnemyScoreText.setPosition(1440.0f, 610.0f);
	mEnemyScoreText.setFillColor(sf::Color::Black);
	mEnemyScoreText.setCharacterSize(200);
	
	/*Setup Sprites*/
	mBackgroundImage.setTexture(mGameReference.GetCommonStore().GetTextureRef("BoardBackground"));
	mBackgroundImage.setPosition(0.0f, 0.0f);

}

void BoardState::HandleInput()
{
}

void BoardState::Update(float dt)
{



	mEnemy.Update(dt);
}

void BoardState::Draw()
{
	mGameReference.GetWindow().clear();
	/*Draw Background*/
	mGameReference.GetWindow().draw(mBackgroundImage);

	/*Draw Scores*/
	mGameReference.GetWindow().draw(mPlayerScoreText);
	mGameReference.GetWindow().draw(mEnemyScoreText);

	/*Draw Player*/
	mGameReference.GetPlayer().Draw();

	/*Draw Enemy*/
	mEnemy.Draw();
}

void BoardState::HandleEvents(sf::Event & ev)
{
	if (ev.type == sf::Event::MouseButtonPressed &&
		ev.mouseButton.button == sf::Mouse::Left)
	{
		/*Capture Mouse Coords*/
		const int xX = sf::Mouse::getPosition(mGameReference.GetWindow()).x;
		const int yY = sf::Mouse::getPosition(mGameReference.GetWindow()).y;
		if (mSelectCard_Player.contains(float(xX), float(yY)))
		{
			if (mGameReference.GetPlayer().GetClickedCard(mSelectCard_Player).GetState() == Card::CardState::Free)
			{
				mGameReference.GetPlayer().GetClickedCard(mSelectCard_Player).SetState(Card::CardState::Selected);
			}
			else
			{
				mGameReference.GetPlayer().GetClickedCard(mSelectCard_Player).SetState(Card::CardState::Free);
			}
		}
		if (mSelectCard_Enemy.contains(float(xX), float(yY)))
		{
			int p = 0;
		}
	}

	if (ev.type == sf::Event::MouseButtonPressed &&
		ev.mouseButton.button == sf::Mouse::Right)
	{
		/*Capture Mouse Coords*/
		const int xX = sf::Mouse::getPosition(mGameReference.GetWindow()).x;
		const int yY = sf::Mouse::getPosition(mGameReference.GetWindow()).y;
		if (mSelectCard_Player.contains(float(xX), float(yY)))
		{
			int p = 0;
		}
		if (mSelectCard_Enemy.contains(float(xX), float(yY)))
		{
			int p = 0;
		}
	}
}

BoardState::BoardState(Game& ref)
	:
	mGameReference(ref),
	mBackgroundImage(),
	mBackgroundFill(),
	mEnemy(ref)
{
	mBackgroundFill.setFillColor(sf::Color::Black);
	mBackgroundFill.setSize(sf::Vector2f(1920, 1080));
	mBackgroundFill.setPosition(sf::Vector2f(0, 0));

	/*Set Rectangles For Card Selection*/
	mSelectCard_Player.left = 200.0f;
	mSelectCard_Player.top = 200.0f;
	mSelectCard_Player.width = 250.0f;
	mSelectCard_Player.height = 300.0f;

	mSelectCard_Enemy.left = 1470.0f;
	mSelectCard_Enemy.top = 200.0f;
	mSelectCard_Enemy.width = 250.0f;
	mSelectCard_Enemy.height = 300.0f;
}


BoardState::~BoardState()
{
}
