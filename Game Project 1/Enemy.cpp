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
	return *CardDeck.back();
}

void Enemy::CycleDeck()
{

	CardDeckIterator = CardDeck.begin();
	Card* tmp = CardDeck.back();
	CardDeck.pop_back();
	CardDeck.insert(CardDeckIterator, tmp);
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

	//Check Slot On Board.
	for(auto& u : brd.GetSlots())
	{
		//Slot if used and the card belongs to the player
		if (u.GetIsUsed() && u.mCard->GetOwner() == Card::CardOwner::Player_Owned)
		{
			//Store Postion and Potential surrounding slot positions of the slot/card
			const sf::Vector2i DeckCardPosition = u.mBoardPosition;
			const sf::Vector2i PositionAbove = sf::Vector2i(u.mBoardPosition.x, u.mBoardPosition.y - 1);
			const sf::Vector2i PositionDown = sf::Vector2i(u.mBoardPosition.x, u.mBoardPosition.y + 1);
			const sf::Vector2i PositionLeft = sf::Vector2i(u.mBoardPosition.x - 1, u.mBoardPosition.y);
			const sf::Vector2i PositionRight = sf::Vector2i(u.mBoardPosition.x + 1, u.mBoardPosition.y);
			/*
			for (auto& pc : CardDeck)
			{
				//Slot above card is free
				if (CheckSafeBoardPosition(PositionAbove, brd.mWidth, brd.mHeight))
				{
					if (pc->mValue_Down > u.mCard->mValue_Top)
					{
						brd.GetSlots()[PositionAbove.y * brd.mWidth + PositionAbove.y].mCard = pc;
						//Change Player To Enemy Card
					}
				}
				//Slot Down card is free
				if (CheckSafeBoardPosition(PositionDown, brd.mWidth, brd.mHeight))
				{
					if (pc->mValue_Top > u.mCard->mValue_Down)
					{
						brd.GetSlots()[PositionDown.y * brd.mWidth + PositionDown.y].mCard = pc;
						//Change Player To Enemy Card
					}
				}
				//Slot left card is free
				if (CheckSafeBoardPosition(PositionLeft, brd.mWidth, brd.mHeight))
				{
					if (pc->mValue_Right > u.mCard->mValue_Left)
					{
						brd.GetSlots()[PositionLeft.y * brd.mWidth + PositionLeft.y].mCard = pc;
						//Change Player To Enemy Card
					}
				}
				//Slot right card is free
				if (CheckSafeBoardPosition(PositionRight, brd.mWidth, brd.mHeight))
				{
					if (pc->mValue_Left > u.mCard->mValue_Right)
					{
						brd.GetSlots()[PositionRight.y * brd.mWidth + PositionRight.y].mCard = pc;
						//Change Player To Enemy Card
					}
				}
			}
			*/
		}
	}

	/*No Win Found*/
	brd.ToogleTurn();

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
	mSprite.setTexture(mGameReference.GetCommonStore().GetTextureRef("EnemyPicture"));
	mSprite.setPosition(x, y);
	mName.setFont(mGameReference.GetCommonStore().GetFontRef("System"));
	mName.setString(name);
	mName.setPosition(xn, yn);
	mName.setFillColor(sf::Color::Black);
	mName.setCharacterSize(18);

	crd1.Initiate(1620.0f, 50.0f, "Boss A", Card::CardOwner::Enemy_Owned);
	crd2.Initiate(1570.0f, 100.0f, "Boss B", Card::CardOwner::Enemy_Owned);
	crd3.Initiate(1520.0f, 150.0f, "Boss C", Card::CardOwner::Enemy_Owned);
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
	for (int p = 0; p < CardDeck.size(); p++)
	{
		CardDeck[p]->SetPosition(1670 - ((p + 1) * 50), ((p + 1) * 50));
		CardDeck[p]->Draw();
	}
}
