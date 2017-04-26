#include "BoardState.h"
#include "Game.h"


void BoardState::Initiate()
{
	/*Only Initiate Once*/
	if (mInitiated)
		return;
	else
		mInitiated = true;

	/*Fill Slot Array*/
	mSlots.push_back(A1);
	mSlots.push_back(A2);
	mSlots.push_back(A3);
	mSlots.push_back(B1);
	mSlots.push_back(B2);
	mSlots.push_back(B3);
	mSlots.push_back(C1);
	mSlots.push_back(C2);
	mSlots.push_back(C3);

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

	mSelectionBoarder.setTexture(mGameReference.GetCommonStore().GetTextureRef("SelectBoarder"));
}

void BoardState::HandleInput()
{
}

void BoardState::Update(float dt)
{
	if (mCurrentTurn == TurnState::EnemyTurn)
	{
		//Added Enemy Turn Here.
		mEnemy.Turn(*this);
	}
	if (mCurrentTurn == TurnState::PlayerTurn)
	{

	}

	mEnemy.Update(dt);
	mGameReference.GetPlayer().Update(dt);

	/*Update Board Cards*/
	for (auto& u : mBoardCardDeck)
	{
		u->Update(dt);
	}

	/*Selected State Update Logic*/
	mSelectFlashCounter += dt;
	if (mSelectFlashCounter > mSelectFlashTimer)
	{
		mSelectFlashCounter = 0.0f;

		if (mShowSelectBoarder == false)
		{
			mShowSelectBoarder = true;
		}
		else if (mShowSelectBoarder == true)
		{
			mShowSelectBoarder = false;
		}
	}
}

void BoardState::Draw()
{
	mGameReference.GetWindow().clear();
	/*Draw Background*/
	mGameReference.GetWindow().draw(mBackgroundImage);

	/*Draw Selection Boarders*/
	if (mSelectSlotState && mShowSelectBoarder)
	{
		for (auto& b : mSlots)
		{
			if (!b.GetIsUsed())
			{
				mSelectionBoarder.setPosition(sf::Vector2f(b.GetFullRectangle().left, b.GetFullRectangle().top));
				mGameReference.GetWindow().draw(mSelectionBoarder);
			}
		}
	}

	/*Draw Scores*/
	mGameReference.GetWindow().draw(mPlayerScoreText);
	mGameReference.GetWindow().draw(mEnemyScoreText);

	/*Draw Player*/
	mGameReference.GetPlayer().Draw();

	/*Draw Enemy*/
	mEnemy.Draw();

	/*Draw Board Card Deck*/
	for (auto& u : mBoardCardDeck)
	{
		u->Draw();
	}
}

void BoardState::HandleEvents(sf::Event & ev)
{
	/*Process Events When Its The Players Turn*/
	if (mCurrentTurn == TurnState::PlayerTurn)
	{
		/*Handle Left Mouse Clicks*/
		if (ev.type == sf::Event::MouseButtonPressed &&
			ev.mouseButton.button == sf::Mouse::Left)
		{
			/*Capture Mouse Click Coords*/
			const int xX = sf::Mouse::getPosition(mGameReference.GetWindow()).x;
			const int yY = sf::Mouse::getPosition(mGameReference.GetWindow()).y;

			/*If Player Has Cards In Their Deck
			and Click Was On One Of Said Cards*/
			if (mGameReference.GetPlayer().GetDeckCount() > 0 &&
				mGameReference.GetPlayer().GetTopCard().GetRectangle().contains(float(xX), float(yY)))
			{
				if (mGameReference.GetPlayer().GetTopCard().GetState() == Card::CardState::Free)
				{
					/*Select Card and Set Board To Selected State*/
					mGameReference.GetPlayer().GetTopCard().SetState(Card::CardState::Selected);
					mSelectSlotState = true;
				}
				else
				{
					/*Free Card and Set Board To Free State*/
					mGameReference.GetPlayer().GetTopCard().SetState(Card::CardState::Free);
					mSelectSlotState = false;
				}
			}

			/*Process Clicks Unique to Board being in Select State*/
			if (mSelectSlotState)
			{
				for (auto& c : mSlots)
				{
					if (c.GetCardRectangle().contains(float(xX), float(yY)) &&
						!c.GetIsUsed())
					{
						c.ToogleUse();
						mSelectSlotState = false;
						mGameReference.GetPlayer().GetTopCard().SetState(Card::CardState::Free);
						mGameReference.GetPlayer().GetTopCard().SetPosition(c.GetCardRectangle().left, c.GetCardRectangle().top);
						mBoardCardDeck.push_back(&mGameReference.GetPlayer().UseTopCard());
						ToogleTurn();
					}
				}
			}
		}


		/*Handle Right Mouse Clicks*/
		if (ev.type == sf::Event::MouseButtonPressed &&
			ev.mouseButton.button == sf::Mouse::Right)
		{
			/*Capture Mouse Coords*/
			const int xX = sf::Mouse::getPosition(mGameReference.GetWindow()).x;
			const int yY = sf::Mouse::getPosition(mGameReference.GetWindow()).y;
			if (mSelectCard_Player.contains(float(xX), float(yY)))
			{
				mSelectSlotState = false;
				mGameReference.GetPlayer().GetTopCard().SetState(Card::CardState::Free);
				mGameReference.GetPlayer().GetTopCard().ResetColor();
				mGameReference.GetPlayer().CycleDeck();
			}
		}
	}
}

void BoardState::ToogleTurn()
{
	if (mCurrentTurn == TurnState::EnemyTurn)
	{
		mCurrentTurn = TurnState::PlayerTurn;
	}
	else if (mCurrentTurn == TurnState::PlayerTurn)
	{
		mCurrentTurn = TurnState::EnemyTurn;
	}
}

BoardState::BoardState(Game& ref)
	:
	mGameReference(ref),
	mBackgroundImage(),
	mBackgroundFill(),
	mEnemy(ref),
	mBoardCardDeck()
{
	mBackgroundFill.setFillColor(sf::Color::Black);
	mBackgroundFill.setSize(sf::Vector2f(1920, 1080));
	mBackgroundFill.setPosition(sf::Vector2f(0, 0));
}


BoardState::~BoardState()
{
}

void BoardState::Slot::ToogleUse()
{
	if (mIsUsed)
	{
		mIsUsed = false;
	}
	else if (!mIsUsed)
	{
		mIsUsed = true;
	}
}
