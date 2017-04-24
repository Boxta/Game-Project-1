#include "BoardState.h"
#include "Game.h"


void BoardState::Initiate()
{
	/*Only Initiate Once*/
	if (mInitiated)
		return;
	else
		mInitiated = true;

	/*Setup Text*/

	mEnemyName.setFont(mGameReference.GetCommonStore().GetFontRef("System"));
	mEnemyName.setString("Donald Trump");
	mEnemyName.setPosition(1703.0f, 721.0f);
	mEnemyName.setFillColor(sf::Color::Black);
	mEnemyName.setCharacterSize(18);

	mPlayerScoreText.setFont(mGameReference.GetCommonStore().GetFontRef("System"));
	mPlayerScoreText.setString("5");
	mPlayerScoreText.setPosition(360.0f, 610.0f);
	mPlayerScoreText.setFillColor(sf::Color::Black);
	mPlayerScoreText.setCharacterSize(200);

	mEnemyScoreText.setFont(mGameReference.GetCommonStore().GetFontRef("System"));
	mEnemyScoreText.setString("3");
	mEnemyScoreText.setPosition(1440.0f, 610.0f);
	mEnemyScoreText.setFillColor(sf::Color::Black);
	mEnemyScoreText.setCharacterSize(200);
	/*Setup Sprites*/
	mBackgroundImage.setTexture(mGameReference.GetCommonStore().GetTextureRef("BoardBackground"));
	mBackgroundImage.setPosition(0.0f, 0.0f);

	mEnemyPicture.setTexture(mGameReference.GetCommonStore().GetTextureRef("EnemyPicture"));
	mEnemyPicture.setPosition(1620.0f, 700.0f);

	mEnemyCard_Img_1.setTexture(mGameReference.GetCommonStore().GetTextureRef("TestCard"));
	mEnemyCard_Img_1.setPosition(1620.0f, 50.0f);
	mEnemyCard_Img_2.setTexture(mGameReference.GetCommonStore().GetTextureRef("TestCard"));
	mEnemyCard_Img_2.setPosition(1570.0f, 100.0f);
	mEnemyCard_Img_3.setTexture(mGameReference.GetCommonStore().GetTextureRef("TestCard"));
	mEnemyCard_Img_3.setPosition(1520.0f, 150.0f);
	mEnemyCard_Img_4.setTexture(mGameReference.GetCommonStore().GetTextureRef("TestCard"));
	mEnemyCard_Img_4.setPosition(1470.0f, 200.0f);
}

void BoardState::HandleInput()
{
}

void BoardState::Update(float dt)
{
}

void BoardState::Draw()
{
	mGameReference.GetWindow().clear();
	/*Draw Background*/
	mGameReference.GetWindow().draw(mBackgroundImage);

	/*Draw Profile Pictures*/
	mGameReference.GetWindow().draw(mEnemyPicture);

	/*Draw Enemy Cards*/
	mGameReference.GetWindow().draw(mEnemyCard_Img_1);
	mGameReference.GetWindow().draw(mEnemyCard_Img_2);
	mGameReference.GetWindow().draw(mEnemyCard_Img_3);
	mGameReference.GetWindow().draw(mEnemyCard_Img_4);

	/*Draw Profile Names*/
	mGameReference.GetWindow().draw(mEnemyName);

	/*Draw Scores*/
	mGameReference.GetWindow().draw(mPlayerScoreText);
	mGameReference.GetWindow().draw(mEnemyScoreText);

	/*Draw Player*/
	mGameReference.GetPlayer().Draw();
}

void BoardState::HandleEvents(sf::Event & ev)
{
}

BoardState::BoardState(Game& ref)
	:
	mGameReference(ref),
	mBackgroundImage(),
	mBackgroundFill(),
	mEnemyCard_Img_1(),
	mEnemyCard_Img_2(),
	mEnemyCard_Img_3(),
	mEnemyCard_Img_4()
{
	mBackgroundFill.setFillColor(sf::Color::Black);
	mBackgroundFill.setSize(sf::Vector2f(1920, 1080));
	mBackgroundFill.setPosition(sf::Vector2f(0, 0));
}


BoardState::~BoardState()
{
}
