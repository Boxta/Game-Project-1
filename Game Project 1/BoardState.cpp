#include "BoardState.h"
#include "Game.h"

BoardState::BoardState(Game& ref)
	:
	mGameReference(ref),
	mEnemy(ref)
{
	/*Setup Background*/
	mBackgroundFill.setFillColor(sf::Color::White);
	mBackgroundFill.setSize(sf::Vector2f(1920, 1080));
	mBackgroundFill.setPosition(sf::Vector2f(0, 0));

	/*Fill Slot Array*/
	mSlots.push_back(A1);
	mSlots.push_back(A2);
	mSlots.push_back(A3);
	mSlots.push_back(A4);
	mSlots.push_back(B1);
	mSlots.push_back(B2);
	mSlots.push_back(B3);
	mSlots.push_back(B4);
	mSlots.push_back(C1);
	mSlots.push_back(C2);
	mSlots.push_back(C3);
	mSlots.push_back(C4);
}

BoardState::~BoardState()
{
	if (mBoardCards.size() > 0)
	{
		for (auto *t : mBoardCards)
		{
			delete t;
		}
	}
}

void BoardState::Initiate()
{
	/*Only Initiate Once*/
	if (mInitiated)
		return;
	else
		mInitiated = true;

	/*Setup Enemy*/
	mEnemy.Initiate(455.0f, 520.0f, "Donald Trump");
	
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

	mTurnIndicator.setTexture(mGameReference.GetCommonStore().GetTextureRef("TurnIcons"));
	mTurnIndicator.setPosition(278.0f, 405.0f);
	mTurnIndicator.setTextureRect(sf::IntRect(173, 0, 173, 256));
	
	mDrawButton.setTexture(mGameReference.GetCommonStore().GetTextureRef("DrawButtons"));
	mDrawButton.setPosition(265.0f, 40.0f); 
	mDrawButton.setTextureRect(sf::IntRect(0, 0, 150, 60));
}

void BoardState::HandleInput()
{
}

void BoardState::Update(float dt)
{
	/*Update Enemy*/
	mEnemy.Update(dt);

	/*Update Player*/
	mGameReference.GetPlayer().Update(dt);

	/*Game Over Logic*/
	if (mGameWinState != WinState::GameRunning)
	{
		mDrawButton.setTextureRect(sf::IntRect(150, 0, 150, 60));
	}
	
	/*Game Is Running Logic*/
	if (mGameWinState == WinState::GameRunning)
	{
		/*Update Draw Button Texture*/
		if (mCurrentTurn == TurnState::PlayerTurn)
		{
			if (!mGameReference.GetPlayer().IsCardDrawn())
			{
				if (mDrawButton.getGlobalBounds().contains(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y))
				{
					mDrawButton.setTextureRect(sf::IntRect(300, 0, 150, 60));
				}
				else
				{
					mDrawButton.setTextureRect(sf::IntRect(0, 0, 150, 60));
				}
			}
			else
			{
				mDrawButton.setTextureRect(sf::IntRect(150, 0, 150, 60));
			}

		}
		else if (mCurrentTurn == TurnState::EnemyTurn)
		{
			mDrawButton.setTextureRect(sf::IntRect(150, 0, 150, 60));
		}

		/*Switch Turns*/
		if (mIsTurning && mCurrentTurn == TurnState::EnemyTurn)
		{
			mTurnIndicator.setTextureRect(sf::IntRect(173, 0, 173, 256));
			mIsTurning = false;
			mCurrentTurn = TurnState::PlayerTurn;
		}
		else if (mIsTurning && mCurrentTurn == TurnState::PlayerTurn)
		{
			/*Turn Counter Increments*/
			mTurnCounter += dt;

			/*Alter Objects During Enemy Turn Countdown*/
			mEnemy.SetCardDrawn(true);
			mDrawButton.setTextureRect(sf::IntRect(150, 0, 150, 60));
			mTurnIndicator.setTextureRect(sf::IntRect(0, 0, 173, 256));

			/*Execute Enemy Turn*/
			if (mTurnCounter > mTurnWait)
			{
				mCurrentTurn = TurnState::EnemyTurn;
				mIsTurning = false;
				mTurnCounter = 0.0f;
				mEnemy.Turn(*this);
			}
		}

		/*Selected State Boarder Draw Timer*/
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

		/*Calculate Score*/
		mPlayerScore = 0;
		mEnemyScore = 0;

		for (auto& R : mSlots)
		{
			if (R.GetIsUsed() && R.GetOwner() == Slot::Owner::Player_Owned)
			{
				mPlayerScore++;
			}
			if (R.GetIsUsed() && R.GetOwner() == Slot::Owner::Enemy_Owned)
			{
				mEnemyScore++;
			}
		}

		/*Convert Score Ints To Strings For Draw*/
		mEnemyScoreText.setString(std::to_string(mEnemyScore));
		mPlayerScoreText.setString(std::to_string(mPlayerScore));

		/*Set Win State*/
		if ((mEnemyScore + mPlayerScore) >= 8)
		{
			if (mEnemyScore < mPlayerScore)
			{
				mGameWinState = WinState::PlayerWin;
			}
			else if (mEnemyScore > mPlayerScore)
			{
				mGameWinState = WinState::EnemyWin;
			}
			else if (mEnemyScore == mPlayerScore)
			{
				mGameWinState = WinState::Tie;
			}
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
	
	mGameReference.GetWindow().draw(mTurnIndicator);
	mGameReference.GetWindow().draw(mDrawButton);

	for (iterator = mBoardCards.begin(), end = mBoardCards.end(); iterator != end; ++iterator)
	{
		(*iterator)->Draw(mGameReference.GetWindow());
	}

	/*Draw Scores*/
	//mGameReference.GetWindow().draw(mPlayerScoreText);
	//mGameReference.GetWindow().draw(mEnemyScoreText);

	/*Draw Player*/
	mGameReference.GetPlayer().Draw();

	/*Draw Enemy*/
	mEnemy.Draw();
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

			/*Process Clicks When Board Is In Select State*/
			if (mSelectSlotState)
			{
				/*Process Player Clicking Their Selected ard Again*/
				if (mGameReference.GetPlayer().GetTopCard().GetRectangle().contains(float(xX), float(yY)))
				{
					mGameReference.GetPlayer().GetTopCard().SetState(Card::CardState::Free);
					mSelectSlotState = false;
					return;
				}

				/*Process Player Clicking A Board Slot*/
				for (auto& c : mSlots)
				{
					if (c.GetCardRectangle().contains(float(xX), float(yY)) &&
						!c.GetIsUsed())
					{
						/*Turn off the boards selection state*/
						mSelectSlotState = false;

						/*Player Takes Turn*/
						mGameReference.GetPlayer().Turn(*this, float(c.GetGridPosition().x), float(c.GetGridPosition().y));
						break;
					}
				}
			}
			else
			{
				/*Check Click For Button*/
				if (mDrawButton.getGlobalBounds().contains(xX, yY) && !mGameReference.GetPlayer().IsCardDrawn())
				{
					mGameReference.GetPlayer().CycleDeck();
				}
				else if (mGameReference.GetPlayer().GetDeckCount() > 0 &&
					mGameReference.GetPlayer().GetTopCard().GetRectangle().contains(float(xX), float(yY)) &&
						mGameReference.GetPlayer().GetTopCard().GetState() == Card::CardState::Free)
				{
						/*Select Card and Set Board To Selected State*/
						mGameReference.GetPlayer().GetTopCard().SetState(Card::CardState::Selected);
						mSelectSlotState = true;
				}
			}
		}
	}
}

BoardState::Slot& BoardState::GetSlot(int x, int y)
{
	for (auto& j : mSlots)
	{
		if (j.GetGridPosition().x == x &&
			j.GetGridPosition().y == y)
			return j;
	}
}

void BoardState::ToogleTurn()
{
	mIsTurning = true;
}

void BoardState::AddCard(Card& card, Slot& slt)
{
	/*Create New Board Card From fValue*/
	Card *temp = new Card(slt.GetCardRectangle().left, slt.GetCardRectangle().top,
		card.GetName(),
		card.GetUp(), card.GetDown(), card.GetLeft(), card.GetRight(),
		mGameReference.GetCommonStore(),
		card.GetTextureRectangle(), card.GetOwner());
	
	/*Associate the Slot and the Card*/
	slt.SetCardReference(temp);
	
	/*Ensure the Slot and Card Owner are Set*/
	if (card.GetOwner() == Card::Owner::None)
	{
		slt.ChangeOwner(BoardState::Slot::Owner::None, temp);
	}
	else if (card.GetOwner() == Card::Owner::Player_Owned)
	{
		slt.ChangeOwner(BoardState::Slot::Owner::Player_Owned, temp);
	}
	else if (card.GetOwner() == Card::Owner::Enemy_Owned)
	{
		slt.ChangeOwner(BoardState::Slot::Owner::Enemy_Owned, temp);
	}

	/*Push the new card into the board card deck*/
	mBoardCards.push_back(temp);
}

void BoardState::Slot::ChangeOwner(Owner own, Card* ref)
{
	switch (own)
	{
	case Owner::None:
		mIsUsed = false;
		mOwner = Owner::None;
		ref->ChangeOwner(Card::Owner::None);
		break;
	case Owner::Player_Owned:
		mIsUsed = true;
		mOwner = Owner::Player_Owned;
		ref->ChangeOwner(Card::Owner::Player_Owned);
		break;
	case Owner::Enemy_Owned:
		mIsUsed = true;
		mOwner = Owner::Enemy_Owned;
		ref->ChangeOwner(Card::Owner::Enemy_Owned);
		break;
	}
}


