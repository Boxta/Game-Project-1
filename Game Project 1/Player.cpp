#include "Player.h"
#include "Game.h"
#include "BoardState.h"

Player::Player(Game& ref)
	:
mGameReference(ref),
crd1(ref),
crd2(ref),
crd3(ref),
crd4(ref)
{
}


Player::~Player()
{
}

void Player::Initiate(float x, float y, 
	std::string name,
	float xn, float yn)
{
	mHandPositionA = { 140.0f, 150.0f };

	mSprite.setTexture(mGameReference.GetCommonStore().GetTextureRef("PlayerPicture"));
	mSprite.setPosition(x, y);
	mName.setFont(mGameReference.GetCommonStore().GetFontRef("System"));
	mName.setString(name);
	mName.setPosition(xn, yn);
	mName.setFillColor(sf::Color::Black);
	mName.setCharacterSize(18);

	crd1.Initiate(0.0f, 0.0f, "Card A", Card::CardOwner::Player_Owned);
	crd2.Initiate(0.0f, 0.0f, "Card B", Card::CardOwner::Player_Owned);
	crd3.Initiate(0.0f, 0.0f, "Card C", Card::CardOwner::Player_Owned);
	crd4.Initiate(0.0f, 0.0f, "Card D", Card::CardOwner::Player_Owned);

	CardDeck.push_back(&crd1);
	CardDeck.push_back(&crd2);
	CardDeck.push_back(&crd3);
	CardDeck.push_back(&crd4);
}

void Player::Update(const float dt)
{
	for (auto& c : CardDeck)
	{
		c->Update(dt);
	}
}

void Player::Draw()
{
	/*Draw Profile Picture*/
	mGameReference.GetWindow().draw(mSprite);

	/*Draw Player Name*/
	mGameReference.GetWindow().draw(mName);
	
	/*If No Cards In Deck Exit*/
	if (CardDeck.size() == 0)
		return;

	for (int T = 0; T < CardDeck.size(); T++)
	{
		if (T < mCardDeckIterator)
		{
			CardDeck[T]->SetPosition(mHandPositionA.x - 125.0f, mHandPositionA.y - 80.0f);
			CardDeck[T]->Draw();
		}
	}

	for (int T = CardDeck.size() - 1; T > 0; T--)
	{
		if (T > mCardDeckIterator)
		{
			CardDeck[T]->SetPosition(mHandPositionA.x + 125.0f, mHandPositionA.y - 80.0f);
			CardDeck[T]->Draw();
		}
	}

	CardDeck[mCardDeckIterator]->SetPosition(mHandPositionA.x, mHandPositionA.y);
	CardDeck[mCardDeckIterator]->Draw();
}

Card& Player::GetTopCard()
{
	return *CardDeck[mCardDeckIterator];
}


void Player::CycleDeck()
{
	if (mIterateDirection)
	{
		if (mCardDeckIterator >= (CardDeck.size() - 1))
		{
			mIterateDirection = false;
			mCardDeckIterator--;
		}
		else
		{
			mCardDeckIterator++;
		}
	}
	else
	{
		if (mCardDeckIterator <= 0)
		{
			mIterateDirection = true;
			mCardDeckIterator++;
		}
		else
		{
			mCardDeckIterator--;
		}
	}
}

void Player::KillTopCard()
{
	if (mCardDeckIterator > 0)
	{
		CardDeck.erase(CardDeck.begin() + mCardDeckIterator);
		mCardDeckIterator--;
	}
	else
	{
		CardDeck.erase(CardDeck.begin() + mCardDeckIterator);
	}
}

void Player::Turn(BoardState& brd, float xX, float yY)
{

	bool mHasWon = false;

	/*Try To Win*/
	for (auto& u : brd.GetSlots())
	{
		if (u.GetCardRectangle().contains(float(xX), float(yY)) &&
			!u.GetIsUsed())
		{
			/*Copy The Players Card To The Slots Card*/
			GetTopCard().CopyCard(*u.mCard);

			/*Mark the Slot As Used*/
			u.ToogleUse();

			/*Mark The Slots Card As Used*/
			u.mCard->SetState(Card::CardState::Used);

			/*Set Slots Card To Position Of The Slot*/
			u.mCard->SetPosition(u.GetCardRectangle().left, u.GetCardRectangle().top);

			//Store Postion and Potential surrounding slot positions of the slot/card
			sf::Vector2i DeckCardPosition = u.mBoardPosition;
			sf::Vector2i PositionAbove = sf::Vector2i(u.mBoardPosition.x, u.mBoardPosition.y - 1);
			sf::Vector2i PositionDown = sf::Vector2i(u.mBoardPosition.x, u.mBoardPosition.y + 1);
			sf::Vector2i PositionLeft = sf::Vector2i(u.mBoardPosition.x - 1, u.mBoardPosition.y);
			sf::Vector2i PositionRight = sf::Vector2i(u.mBoardPosition.x + 1, u.mBoardPosition.y);

			//Slot above card is free
			if (CheckSafeBoardPosition(PositionAbove, brd.mWidth, brd.mHeight))
			{
				BoardState::Slot& slt = brd.GetSlot(PositionAbove.x, PositionAbove.y);
				if (slt.GetIsUsed() &&
					slt.mCard->GetOwner() == Card::CardOwner::Enemy_Owned &&
					slt.mCard->mValue_Down < u.mCard->mValue_Top)
				{
					/*Win*/
					slt.mCard->SetOwner(Card::CardOwner::Player_Owned);
					mHasWon = true;
				}
			}
			if (CheckSafeBoardPosition(PositionDown, brd.mWidth, brd.mHeight))
			{
				BoardState::Slot& slt = brd.GetSlot(PositionDown.x, PositionDown.y);
				if (slt.GetIsUsed() &&
					slt.mCard->GetOwner() == Card::CardOwner::Enemy_Owned &&
					slt.mCard->mValue_Top < u.mCard->mValue_Down)
				{
					/*Win*/
					slt.mCard->SetOwner(Card::CardOwner::Player_Owned);
					mHasWon = true;
				}
			}
			if (CheckSafeBoardPosition(PositionLeft, brd.mWidth, brd.mHeight))
			{
				BoardState::Slot& slt = brd.GetSlot(PositionLeft.x, PositionLeft.y);
				if (slt.GetIsUsed() &&
					slt.mCard->GetOwner() == Card::CardOwner::Enemy_Owned &&
					slt.mCard->mValue_Right < u.mCard->mValue_Left)
				{
					/*Win*/
					slt.mCard->SetOwner(Card::CardOwner::Player_Owned);
					mHasWon = true;
				}
			}
			if (CheckSafeBoardPosition(PositionRight, brd.mWidth, brd.mHeight))
			{
				BoardState::Slot& slt = brd.GetSlot(PositionRight.x, PositionRight.y);
				if (slt.GetIsUsed() &&
					slt.mCard->GetOwner() == Card::CardOwner::Enemy_Owned &&
					slt.mCard->mValue_Left < u.mCard->mValue_Right)
				{
					/*Win*/
					slt.mCard->SetOwner(Card::CardOwner::Player_Owned);
					mHasWon = true;
				}
			}
		}
	}
	
	/*Remove Used Card From Players Deck*/
	KillTopCard();

	/*End Player Turn*/
	brd.ToogleTurn();
	
}

bool Player::CheckSafeBoardPosition(sf::Vector2i vec, int boardwidth, int boardheight)
{
	if (vec.x < 0)
	{
		return false;
	}
	else if (vec.x > boardwidth - 1)
	{
		return false;
	}
	else if (vec.y < 0)
	{
		return false;
	}
	else if (vec.y > boardheight - 1)
	{
		return false;
	}
	else
	{
		return true;
	}
}





