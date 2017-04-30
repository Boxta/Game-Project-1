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
	/*Check Game Win*/
	int counterp = 0;
	int countere = 0;
	for (auto& R : mSlots)
	{
		if (R.GetIsUsed())
		{
			if (R.mCard->GetOwner() == Card::CardOwner::Enemy_Owned)
			{
				countere++;
			}
			else if (R.mCard->GetOwner() == Card::CardOwner::Player_Owned)
			{
				counterp++;
			}
		}
	}
	if ((countere + counterp) >= 8)
	{
		if (countere < counterp)
		{
			mGameWinState = WinState::PlayerWin;
		}
		else if(countere > counterp)
		{
			mGameWinState = WinState::EnemyWin;
		}
		else if (countere == counterp)
		{
			mGameWinState = WinState::Tie;
		}
	}

	if (mGameWinState != WinState::GameRunning)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			ResetBoard();
		}
	}

	if (mGameWinState == WinState::GameRunning)
	{
		/*Calculate Score*/
		mPlayerScore = 0;
		mEnemyScore = 0;
		for (auto& t : mSlots)
		{
			t.mCard->Update(dt);
			if (t.mCard->GetOwner() == Card::CardOwner::Player_Owned)
			{
				mPlayerScore++;
			}
			if (t.mCard->GetOwner() == Card::CardOwner::Enemy_Owned)
			{
				mEnemyScore++;
			}
		}

		/*Call Enemy Turn If Its Theirs*/
		if (mCurrentTurn == TurnState::EnemyTurn)
		{
			mEnemy.Turn(*this);
		}

		/*Update Enemy*/
		mEnemy.Update(dt);
		mEnemyScoreText.setString(std::to_string(mEnemyScore));

		/*Update Player*/
		mGameReference.GetPlayer().Update(dt);
		mPlayerScoreText.setString(std::to_string(mPlayerScore));

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
}

void BoardState::Draw()
{
	mGameReference.GetWindow().clear();
	
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
	
	/*Draw Background*/
	mGameReference.GetWindow().draw(mBackgroundImage);

	/*Draw Scores*/
	mGameReference.GetWindow().draw(mPlayerScoreText);
	mGameReference.GetWindow().draw(mEnemyScoreText);

	/*Draw Player*/
	mGameReference.GetPlayer().Draw();

	/*Draw Enemy*/
	mEnemy.Draw();

	/*Draw Board Cards*/
	for (auto& t : mSlots)
	{
		if (t.GetIsUsed())
		{
			t.mCard->Draw();
		}
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
						/*Turn off the boards selection state*/
						mSelectSlotState = false;
						
						/*Player Takes Turn*/
						mGameReference.GetPlayer().Turn(*this, xX, yY);

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
		if (j.mBoardPosition.x == x &&
			j.mBoardPosition.y == y)
			return j;
	}
}

void BoardState::ResetBoard()
{
	mSelectSlotState = false;
	mCurrentTurn = TurnState::PlayerTurn;
	mSelectFlashCounter = 0.0f;
	mShowSelectBoarder = false;
	mGameWinState = WinState::GameRunning;


	/*Reset Score*/
	mPlayerScore = 0;
	mEnemyScore = 0;

	/*Clear Slot Array*/
	mSlots.clear();

	/*Create Board Cards*/
	Card_A1.Initiate(0.0f, 0.0f, "", Card::CardOwner::None);
	Card_A2.Initiate(0.0f, 0.0f, "", Card::CardOwner::None);
	Card_A3.Initiate(0.0f, 0.0f, "", Card::CardOwner::None);
	Card_B1.Initiate(0.0f, 0.0f, "", Card::CardOwner::None);
	Card_B2.Initiate(0.0f, 0.0f, "", Card::CardOwner::None);
	Card_B3.Initiate(0.0f, 0.0f, "", Card::CardOwner::None);
	Card_C1.Initiate(0.0f, 0.0f, "", Card::CardOwner::None);
	Card_C2.Initiate(0.0f, 0.0f, "", Card::CardOwner::None);
	Card_C3.Initiate(0.0f, 0.0f, "", Card::CardOwner::None);
	
	/*Re-Create Slots*/
	A1 = { 0, 0 };
	A2 = { 1, 0 };
	A3 = { 2, 0 };
	B1 = { 0, 1 };
	B2 = { 1, 1 };
	B3 = { 2, 1 };
	C1 = { 0, 2 };
	C2 = { 1, 2 };
	C3 = { 2, 2 };
	
	/*Assign Card References To Slots*/
	A1.mCard = &Card_A1;
	A2.mCard = &Card_A2;
	A3.mCard = &Card_A3;
	B1.mCard = &Card_B1;
	B2.mCard = &Card_B2;
	B3.mCard = &Card_B3;
	C1.mCard = &Card_C1;
	C2.mCard = &Card_C2;
	C3.mCard = &Card_C3;

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
	mEnemy.ClearDeck();

	/*Setup Player*/
	mGameReference.GetPlayer().ClearDeck();
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
	mEnemy(ref),
	Card_A1(ref),
	Card_A2(ref),
	Card_A3(ref),
	Card_B1(ref),
	Card_B2(ref),
	Card_B3(ref),
	Card_C1(ref),
	Card_C2(ref),
	Card_C3(ref)
{
	mBackgroundFill.setFillColor(sf::Color::Black);
	mBackgroundFill.setSize(sf::Vector2f(1920, 1080));
	mBackgroundFill.setPosition(sf::Vector2f(0, 0));
	
	/*Assign Card References To Slots*/
	A1.mCard = &Card_A1;
	A2.mCard = &Card_A2;
	A3.mCard = &Card_A3;
	B1.mCard = &Card_B1;
	B2.mCard = &Card_B2;
	B3.mCard = &Card_B3;
	C1.mCard = &Card_C1;
	C2.mCard = &Card_C2;
	C3.mCard = &Card_C3;
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
