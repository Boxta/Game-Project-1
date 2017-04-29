#include "Enemy.h"
#include "Game.h"
#include "BoardState.h"

Enemy::Enemy(Game& ref)
	:
	mGameReference(ref),
	crd1(ref),
	crd2(ref),
	crd3(ref),
	crd4(ref)
{
}


Enemy::~Enemy()
{
}

Card& Enemy::GetTopCard()
{
	return *CardDeck[mCardDeckIterator];
}

void Enemy::KillTopCard()
{
	CardDeck.erase(CardDeck.begin() + mCardDeckIterator);
}

void Enemy::KillCard(int u)
{
	CardDeck.erase(CardDeck.begin() + u);
}

void Enemy::CycleDeck()
{
	if (mCardDeckIterator == CardDeck.size() - 1)
	{
		mCardDeckIterator = 0;
	}
	else
	{
		mCardDeckIterator++;
	}
}

void Enemy::Turn(BoardState& brd)
{
	bool noSlotsUsed = true;
	for (auto& r : brd.GetSlots())
	{
		if (r.GetIsUsed())
		{
			noSlotsUsed = false;
		}
	}
	if (noSlotsUsed)
		return;

	bool mHasWon = false;

	/*Try To Win*/
	for (auto& u : brd.GetSlots())
	{
		//Slot if used and the card belongs to the player
		if (u.GetIsUsed() && u.mCard->GetOwner() == Card::CardOwner::Player_Owned)
		{
			//Store Postion and Potential surrounding slot positions of the slot/card
			sf::Vector2i DeckCardPosition = u.mBoardPosition;
			sf::Vector2i PositionAbove = sf::Vector2i(u.mBoardPosition.x, u.mBoardPosition.y - 1);
			sf::Vector2i PositionDown = sf::Vector2i(u.mBoardPosition.x, u.mBoardPosition.y + 1);
			sf::Vector2i PositionLeft = sf::Vector2i(u.mBoardPosition.x - 1, u.mBoardPosition.y);
			sf::Vector2i PositionRight = sf::Vector2i(u.mBoardPosition.x + 1, u.mBoardPosition.y);


			for (auto& pc : CardDeck)
			{
				//Slot above card is free
				if (CheckSafeBoardPosition(PositionAbove, brd.mWidth, brd.mHeight))
				{
					BoardState::Slot& slt = brd.GetSlot(PositionAbove.x, PositionAbove.y);
					if (!slt.GetIsUsed() &&
						pc->mValue_Down > u.mCard->mValue_Top)
					{
						/*Win*/
						pc->CopyCard(*slt.mCard);
						slt.mCard->SetPosition(slt.GetCardRectangle().left, slt.GetCardRectangle().top);
						slt.ToogleUse();
						KillTopCard();
						brd.ToogleTurn();
						mHasWon = true;
						break;
					}
				}
				else if (CheckSafeBoardPosition(PositionDown, brd.mWidth, brd.mHeight))
				{
					BoardState::Slot& slt = brd.GetSlot(PositionDown.x, PositionDown.y);
					if (!slt.GetIsUsed() &&
						pc->mValue_Top > u.mCard->mValue_Down)
					{
						pc->CopyCard(*slt.mCard);
						slt.mCard->SetPosition(slt.GetCardRectangle().left, slt.GetCardRectangle().top);
						slt.ToogleUse();
						KillTopCard();
						brd.ToogleTurn();
						mHasWon = true;
						break;
					}
				}
				else if (CheckSafeBoardPosition(PositionLeft, brd.mWidth, brd.mHeight))
				{
					BoardState::Slot& slt = brd.GetSlot(PositionLeft.x, PositionLeft.y);
					if (!slt.GetIsUsed() &&
						pc->mValue_Right > u.mCard->mValue_Left)
					{
						pc->CopyCard(*slt.mCard);
						slt.mCard->SetPosition(slt.GetCardRectangle().left, slt.GetCardRectangle().top);
						slt.ToogleUse();
						KillTopCard();
						brd.ToogleTurn();
						mHasWon = true;
						break;
					}
				}
				else if (CheckSafeBoardPosition(PositionRight, brd.mWidth, brd.mHeight))
				{
					BoardState::Slot& slt = brd.GetSlot(PositionRight.x, PositionRight.y);
					if (!slt.GetIsUsed() &&
						pc->mValue_Left > u.mCard->mValue_Right)
					{

						pc->CopyCard(*slt.mCard);
						slt.mCard->SetPosition(slt.GetCardRectangle().left, slt.GetCardRectangle().top);
						slt.ToogleUse();
						KillTopCard();
						brd.ToogleTurn();
						mHasWon = true;
						break;
					}
				}

			}
		}
	}
	/*Handle Loss*/
	if (!mHasWon)
	{
		/*Setup Random Generator*/
		std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
		std::uniform_int_distribution<int> uni(0, CardDeck.size() - 1); // guaranteed unbiased

		for (auto& u : brd.GetSlots())
		{
			//Slot if used and the card belongs to the player
			if (u.GetIsUsed())
				continue;

			Card* tempcard = nullptr;
			int p = uni(rng);
			do
			{
				p = uni(rng);
			} while (CardDeck[p]->GetState() == Card::CardState::Used);

			/*Lose*/
			CardDeck[p]->CopyCard(*u.mCard);
			u.mCard->SetPosition(u.GetCardRectangle().left, u.GetCardRectangle().top);
			u.ToogleUse();
			KillCard(p);
			brd.ToogleTurn();
			break;
		}
	}
}

bool Enemy::CheckSafeBoardPosition(sf::Vector2i vec, int boardwidth, int boardheight)
{
	if (vec.x < 0)
	{
		return false;
	}
	else if (vec.x > boardwidth)
	{
		return false;
	}
	else if (vec.y < 0)
	{
		return false;
	}
	else if (vec.y > boardheight)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Enemy::Initiate(float x, float y,
	std::string name,
	float xn, float yn)
{
	mHandPositionA = { 1620.0f, 100.0f };
	mHandPositionB = { 1595.0f, 80.0f };
	mHandPositionC = { 1745.0f, 80.0f };
	
	mSprite.setTexture(mGameReference.GetCommonStore().GetTextureRef("EnemyPicture"));
	mSprite.setPosition(x, y);
	mName.setFont(mGameReference.GetCommonStore().GetFontRef("System"));
	mName.setString(name);
	mName.setPosition(xn, yn);
	mName.setFillColor(sf::Color::Black);
	mName.setCharacterSize(18);

	crd1.Initiate(1620.0f, 50.0f, "Dragon", Card::CardOwner::Enemy_Owned);
	crd2.Initiate(1570.0f, 100.0f, "Planet", Card::CardOwner::Enemy_Owned);
	crd3.Initiate(1520.0f, 150.0f, "B Hole", Card::CardOwner::Enemy_Owned);
	crd4.Initiate(1470.0f, 200.0f, "Boss D", Card::CardOwner::Enemy_Owned);
	
	CardDeck.push_back(&crd1);
	CardDeck.push_back(&crd2);
	CardDeck.push_back(&crd3);
	CardDeck.push_back(&crd4);
}

void Enemy::Update(const float dt)
{
	for (auto& c : CardDeck)
	{
		c->Update(dt);
	}
}

void Enemy::Draw()
{
	mGameReference.GetWindow().draw(mSprite);
	mGameReference.GetWindow().draw(mName);
	
	if (CardDeck.size() == 0)
		return;

	/*Draw Cards*/
	if (mCardDeckIterator == 0)
	{
		if (CardDeck.size() > 1)
		{
			CardDeck[mCardDeckIterator + 1]->SetPosition(mHandPositionB.x, mHandPositionB.y);
			CardDeck[mCardDeckIterator + 1]->Draw();
		}
		if (CardDeck.size() > 2)
		{
			CardDeck[CardDeck.size() - 1]->SetPosition(mHandPositionC.x, mHandPositionC.y);
			CardDeck[CardDeck.size() - 1]->Draw();
		}

		CardDeck[mCardDeckIterator]->SetPosition(mHandPositionA.x, mHandPositionA.y);
		CardDeck[mCardDeckIterator]->Draw();
	}
	else if (mCardDeckIterator > 0 && mCardDeckIterator < CardDeck.size() - 1)
	{
		if (CardDeck.size() > 1)
		{
			CardDeck[mCardDeckIterator + 1]->SetPosition(mHandPositionB.x, mHandPositionB.y);
			CardDeck[mCardDeckIterator + 1]->Draw();
		}
		if (CardDeck.size() > 2)
		{
			CardDeck[mCardDeckIterator - 1]->SetPosition(mHandPositionC.x, mHandPositionC.y);
			CardDeck[mCardDeckIterator - 1]->Draw();
		}
		CardDeck[mCardDeckIterator]->SetPosition(mHandPositionA.x, mHandPositionA.y);
		CardDeck[mCardDeckIterator]->Draw();
	}
	else if (mCardDeckIterator == CardDeck.size() - 1)
	{
		if (CardDeck.size() > 1)
		{
			CardDeck[0]->SetPosition(mHandPositionB.x, mHandPositionB.y);
			CardDeck[0]->Draw();
		}
		if (CardDeck.size() > 2)
		{
			CardDeck[mCardDeckIterator - 1]->SetPosition(mHandPositionC.x, mHandPositionC.y);
			CardDeck[mCardDeckIterator - 1]->Draw();
		}
		CardDeck[mCardDeckIterator]->SetPosition(mHandPositionA.x, mHandPositionA.y);
		CardDeck[mCardDeckIterator]->Draw();
	}
}
