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
	for (auto& t : mSlots)
	{
		t.mCard->Update(dt);
	}

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
						//mGameReference.GetPlayer().GetTopCard().SetPosition(c.GetCardRectangle().left, c.GetCardRectangle().top);
						/*Copy The Players Card To The Slots Card*/
						mGameReference.GetPlayer().GetTopCard().CopyCard(*c.mCard);
						
						/*Mark the Slot As Used*/
						c.ToogleUse();
						
						/*Mark The Slots Card As Used*/
						c.mCard->SetState(Card::CardState::Used);
						
						/*Set Slots Card To Position Of The Slot*/
						c.mCard->SetPosition(c.GetCardRectangle().left, c.GetCardRectangle().top);
						
						/*Remove Used Card From Players Deck*/
						mGameReference.GetPlayer().KillTopCard();

						/*End Player Turn*/
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
			if (mGameReference.GetPlayer().GetTopCard().GetRectangle().contains(float(xX), float(yY)))
			{
				mSelectSlotState = false;
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
