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
	mSlots.push_back(B1);
	mSlots.push_back(B2);
	mSlots.push_back(B3);
	mSlots.push_back(C1);
	mSlots.push_back(C2);
	mSlots.push_back(C3);
}

BoardState::~BoardState()
{
}

void BoardState::Initiate()
{
	/*Only Initiate Once*/
	if (mInitiated)
		return;
	else
		mInitiated = true;

	/*Setup Enemy*/
	mEnemy.Initiate(1620.0f, 700.0f, "Donald Trump");
	
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

	mBatButton.setTexture(mGameReference.GetCommonStore().GetTextureRef("BatButtons"));
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
	

	/*Countdown Enemy Turn*/
	if (mIsTurning)
	{
		mTurnCounter += dt;
		if (mTurnCounter > mTurnWait)
		{
			mIsTurning = false;
			mTurnCounter = 0.0f;
			if (mCurrentTurn == TurnState::EnemyTurn)
			{
				mCurrentTurn = TurnState::PlayerTurn;
			}
			else if (mCurrentTurn == TurnState::PlayerTurn)
			{
				mIsTurning = true; mCurrentTurn = TurnState::EnemyTurn;
				mEnemy.Turn(*this);
			}
		}
	}

	if (mGameWinState != WinState::GameRunning)
	{
		//do sumting
	}
	if (mGameWinState == WinState::GameRunning)
	{
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
	}

	mPlayerScore = 0;
	mEnemyScore = 0;

	/*Calculate Score*/
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

	/*Convert Score Ints To Strings For Draw*/
	mEnemyScoreText.setString(std::to_string(mEnemyScore));
	mPlayerScoreText.setString(std::to_string(mPlayerScore));
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
						/*Turn off the boards selection state*/
						mSelectSlotState = false;
						
						/*Player Takes Turn*/
						mGameReference.GetPlayer().Turn(*this, float(c.GetGridPosition().x), float(c.GetGridPosition().y));
						break;
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

			if (mGameReference.GetPlayer().GetDeckCount() > 0 &&
				mGameReference.GetPlayer().GetTopCard().GetRectangle().contains(float(xX), float(yY)))
			{
				mSelectSlotState = false;
				mGameReference.GetPlayer().CycleDeck();
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

void BoardState::Slot::ChangeOwner(Owner own, Card& crd)
{
	switch (own)
	{
	case Owner::None:
		mIsUsed = false;
		mOwner = Owner::None;
		crd.ChangeOwner(Card::Owner::None);
		break;
	case Owner::Player_Owned:
		mIsUsed = true;
		mOwner = Owner::Player_Owned;
		crd.ChangeOwner(Card::Owner::Player_Owned);
		break;
	case Owner::Enemy_Owned:
		mIsUsed = true;
		mOwner = Owner::Enemy_Owned;
		crd.ChangeOwner(Card::Owner::Enemy_Owned);
		break;
	}
}


