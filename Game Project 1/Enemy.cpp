#include "Enemy.h"
#include "Game.h"
#include "BoardState.h"

Enemy::Enemy(Game& ref)
	:
	mGameReference(ref),
	rng(rd())
{
}


Enemy::~Enemy()
{
}

Card& Enemy::GetTopCard()
{
	return CardDeck[mCardDeckIterator];
}

Card & Enemy::GetCard(const sf::FloatRect id)
{
	for (auto& U : CardDeck)
	{
		if (U.GetRectangle() == id)
		{
			return U;
		}
	}
}

void Enemy::KillCard(int u)
{
	CardDeck.erase(CardDeck.begin() + u);
}

void Enemy::CycleDeck()
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
		//For All Slots Owner By The Player
		if (u.GetIsUsed() && u.GetOwner() == BoardState::Slot::Owner::Player_Owned)
		{
			//Get The Card Reference
			Card& tempcard = mGameReference.GetPlayer().GetCard(u.GetCardRectangle());

			//Store Potential surrounding slot positions of the slot/card
			const sf::Vector2i DeckCardPosition = { int(u.GetCardRectangle().left), int(u.GetCardRectangle().top) };
			const sf::Vector2i PositionAbove = sf::Vector2i(DeckCardPosition.x, DeckCardPosition.y - 1);
			const sf::Vector2i PositionDown = sf::Vector2i(DeckCardPosition.x, DeckCardPosition.y + 1);
			const sf::Vector2i PositionLeft = sf::Vector2i(DeckCardPosition.x - 1, DeckCardPosition.y);
			const sf::Vector2i PositionRight = sf::Vector2i(DeckCardPosition.x + 1, DeckCardPosition.y);

			for (auto& mycard : CardDeck)
			{
				//Slot above card is free
				if (CheckSafeBoardPosition(PositionAbove, brd.mWidth, brd.mHeight))
				{
					BoardState::Slot& slt = brd.GetSlot(PositionAbove.x, PositionAbove.y);
					if (!slt.GetIsUsed() &&
						mycard.GetDown() > tempcard.GetUp())
					{
						/*Change Enemy Card Values*/
						mycard.SetPosition(slt.GetCardRectangle().left, slt.GetCardRectangle().top);
						mycard.SetState(Card::CardState::Used);
						
						/*Change Board Slot Values*/
						slt.SetUse(true);
						
						/*Take Players Slot/Card*/
						u.ChangeOwner(BoardState::Slot::Owner::Enemy_Owned);
						
						/*Tell Enemy Not To Try and Handle A Loss Scenario*/
						mHasWon = true;

						/*Tell The Board Its Turn Over*/
						brd.ToogleTurn();
						break;
					}
				}
				else if (CheckSafeBoardPosition(PositionDown, brd.mWidth, brd.mHeight))
				{
					BoardState::Slot& slt = brd.GetSlot(PositionDown.x, PositionDown.y);
					if (!slt.GetIsUsed() &&
						mycard.GetUp() > tempcard.GetDown())
					{
						/*Change Enemy Card Values*/
						mycard.SetPosition(slt.GetCardRectangle().left, slt.GetCardRectangle().top);
						mycard.SetState(Card::CardState::Used);

						/*Change Board Slot Values*/
						slt.SetUse(true);

						/*Take Players Slot/Card*/
						u.ChangeOwner(BoardState::Slot::Owner::Enemy_Owned);

						/*Tell Enemy Not To Try and Handle A Loss Scenario*/
						mHasWon = true;

						/*Tell The Board Its Turn Over*/
						brd.ToogleTurn();
						break;
					}
				}
				else if (CheckSafeBoardPosition(PositionLeft, brd.mWidth, brd.mHeight))
				{
					BoardState::Slot& slt = brd.GetSlot(PositionLeft.x, PositionLeft.y);
					if (!slt.GetIsUsed() &&
						mycard.GetRight() > tempcard.GetLeft())
					{
						/*Change Enemy Card Values*/
						mycard.SetPosition(slt.GetCardRectangle().left, slt.GetCardRectangle().top);
						mycard.SetState(Card::CardState::Used);

						/*Change Board Slot Values*/
						slt.SetUse(true);

						/*Take Players Slot/Card*/
						u.ChangeOwner(BoardState::Slot::Owner::Enemy_Owned);

						/*Tell Enemy Not To Try and Handle A Loss Scenario*/
						mHasWon = true;

						/*Tell The Board Its Turn Over*/
						brd.ToogleTurn();
						break;
					}
				}
				else if (CheckSafeBoardPosition(PositionRight, brd.mWidth, brd.mHeight))
				{
					BoardState::Slot& slt = brd.GetSlot(PositionRight.x, PositionRight.y);
					if (!slt.GetIsUsed() &&
						mycard.GetLeft() > tempcard.GetRight())
					{
						/*Change Enemy Card Values*/
						mycard.SetPosition(slt.GetCardRectangle().left, slt.GetCardRectangle().top);
						mycard.SetState(Card::CardState::Used);

						/*Change Board Slot Values*/
						slt.SetUse(true);

						/*Take Players Slot/Card*/
						u.ChangeOwner(BoardState::Slot::Owner::Enemy_Owned);

						/*Tell Enemy Not To Try and Handle A Loss Scenario*/
						mHasWon = true;

						/*Tell The Board Its Turn Over*/
						brd.ToogleTurn();
						break;
					}
				}

			}
		}
	}
	
	/*If No Win Then Handle Loss*/
	if (!mHasWon)
	{
		/*Setup Random Generator*/
		std::uniform_int_distribution<int> uni(0, CardDeck.size() - 1); // guaranteed unbiased

		for (auto& u : brd.GetSlots())
		{
			//Find Free Slot
			if (u.GetIsUsed())
				continue;

			Card* tempcard = nullptr;
			int p = uni(rng);
			do
			{
				p = uni(rng);
			} while (CardDeck[p].GetState() == Card::CardState::Used);

			/*Change Enemy Card Values*/
			CardDeck[p].SetPosition(u.GetCardRectangle().left, u.GetCardRectangle().top);
			CardDeck[p].SetState(Card::CardState::Used);

			/*Change Board Slot Values*/
			u.SetUse(true);

			/*Tell The Board Its Turn Over*/
			brd.ToogleTurn();
			break;
		}
	}
}

void Enemy::ClearDeck()
{
	CardDeck.clear();
}

void Enemy::AddCard(float posx, float posy, std::string name, int U, int D, int L, int R)
{
	Card aCard = { posx, posy, 
		name, 
		U, D, L, R, 
		mGameReference.GetCommonStore(),
		sf::IntRect(250, 300, 250, 300) };
	CardDeck.push_back(aCard);
}


Card& Enemy::GetWorstCard()
{
	Card* ref = nullptr;
	for (auto& C : CardDeck)
	{
		if (C.GetState() == Card::CardState::Used)
			continue;
		
		/*If Ref Empty Give It First Card*/
		if (ref == nullptr)
			ref = &C;
		
		/*Else Check If This Cards Values Are Greater Than Refs*/
		int P = C.GetLeft() + C.GetRight() + C.GetDown() + C.GetUp();
		int R = ref->GetLeft() + ref->GetRight() + ref->GetDown() + ref->GetUp();
	
		if (P > R)
			ref = &C;
	}

	return *ref;
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
	std::string name)
{
	mHandPositionA = { 1530.0f, 150.0f };
	
	mSprite.setTexture(mGameReference.GetCommonStore().GetTextureRef("EnemyPicture"));
	mSprite.setPosition(x, y);
	mName.setFont(mGameReference.GetCommonStore().GetFontRef("System"));
	mName.setString(name);

	mName.setFillColor(sf::Color::Black);
	mName.setCharacterSize(18);
	mName.setPosition(x + mName_XOffset, y + mName_YOffset);
	AddCard(0.0f, 0.0f, "Dragon", 3, 4, 3, 4);
	AddCard(0.0f, 0.0f, "Planet", 3, 4, 3, 4);
	AddCard(0.0f, 0.0f, "Gemini", 3, 4, 3, 4);
	AddCard(0.0f, 0.0f, "Roadie", 3, 4, 3, 4);
}

void Enemy::Update(const float dt)
{

}

void Enemy::Draw()
{
	mGameReference.GetWindow().draw(mSprite);
	mGameReference.GetWindow().draw(mName);
	
	if (CardDeck.size() == 0)
		return;

	/*Draw Player Cards In Deck*/
	for (int T = 0; T < CardDeck.size(); T++)
	{
		if (T < mCardDeckIterator &&
			CardDeck[T].GetState() != Card::CardState::Used)
		{
			CardDeck[T].SetPosition(mHandPositionA.x - 125.0f, mHandPositionA.y - 80.0f);
			CardDeck[T].Draw(mGameReference.GetWindow());
		}
	}
	for (int T = 0; T < CardDeck.size(); T++)
	{
		if (T > mCardDeckIterator &&
			CardDeck[T].GetState() != Card::CardState::Used)
		{
			CardDeck[T].SetPosition(mHandPositionA.x + 125.0f, mHandPositionA.y - 80.0f);
			CardDeck[T].Draw(mGameReference.GetWindow());
		}
	}
	for (int T = 0; T < CardDeck.size(); T++)
	{
		if (T == mCardDeckIterator &&
			CardDeck[T].GetState() != Card::CardState::Used)
		{
			CardDeck[mCardDeckIterator].SetPosition(mHandPositionA.x, mHandPositionA.y);
			CardDeck[mCardDeckIterator].Draw(mGameReference.GetWindow());
		}
	}

	/*Draw Used Cards On Board*/
	for (int T = 0; T < CardDeck.size(); T++)
	{
		if (CardDeck[T].GetState() == Card::CardState::Used)
		{
			CardDeck[T].Draw(mGameReference.GetWindow());
		}
	}
}
