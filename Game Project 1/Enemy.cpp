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

Card& Enemy::GetCard(const sf::FloatRect id)
{
	for (auto U : CardDeck)
	{
		if ((*U).GetRectangle() == id)
		{
			return (*U);
		}
	}
}

void Enemy::Turn(BoardState& brd)
{
	/*Check There Is a Free Slot To Use*/
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

	/*Find Player Card On The Board (Enemy MUST take second turn currently.)*/
	for (auto& u : brd.GetSlots())
	{
		if (!u.GetIsUsed())
			continue;

		if (u.GetOwner() == BoardState::Slot::Owner::Enemy_Owned)
			continue;

		//Create Potential Surrounding Slot Positions
		const sf::Vector2i DeckCardPosition = { u.GetGridPosition().x, u.GetGridPosition().y };
		const sf::Vector2i PositionAbove = sf::Vector2i(DeckCardPosition.x, DeckCardPosition.y - 1);
		const sf::Vector2i PositionDown = sf::Vector2i(DeckCardPosition.x, DeckCardPosition.y + 1);
		const sf::Vector2i PositionLeft = sf::Vector2i(DeckCardPosition.x - 1, DeckCardPosition.y);
		const sf::Vector2i PositionRight = sf::Vector2i(DeckCardPosition.x + 1, DeckCardPosition.y);


		/*Check Surrounding Slot Positions Are Valid Board Slot Positions*/
		if (CheckSafeBoardPosition(PositionAbove, brd.mWidth, brd.mHeight))
		{
			/*Catch Board Slot*/
			BoardState::Slot& slt = brd.GetSlot(PositionAbove.x, PositionAbove.y);

			if (!slt.GetIsUsed() &&
				GetTopCard().GetDown() > u.GetCardReference()->GetUp())
			{
				/*Set My Card Into Free Slot*/
				GetTopCard().SetPosition(slt.GetCardRectangle().left, slt.GetCardRectangle().top);

				/*Add Enemies Player Card To Board Card Deck*/
				brd.AddCard(GetTopCard(), slt);

				/*Take Primary Player Card*/
				u.ChangeOwner(BoardState::Slot::Owner::Enemy_Owned, u.GetCardReference());

				/*Set Win State To True*/
				mHasWon = true;

				/*Remove Card From Deck*/
				delete *CardDeck.begin();
				CardDeck.erase(CardDeck.begin());
				break;
			}
		}
		if (CheckSafeBoardPosition(PositionDown, brd.mWidth, brd.mHeight))
		{
			BoardState::Slot& slt = brd.GetSlot(PositionDown.x, PositionDown.y);
			if (!slt.GetIsUsed() &&
				GetTopCard().GetUp() > u.GetCardReference()->GetDown())
			{
				/*Set My Card Into Free Slot*/
				GetTopCard().SetPosition(slt.GetCardRectangle().left, slt.GetCardRectangle().top);
					
				/*Add Enemies Player Card To Board Card Deck*/
				brd.AddCard(GetTopCard(), slt);

				/*Take Primary Player Card*/
				u.ChangeOwner(BoardState::Slot::Owner::Enemy_Owned, u.GetCardReference());

				/*Set Win State To True*/
				mHasWon = true;

				/*Remove Card From Deck*/
				delete *CardDeck.begin();
				CardDeck.erase(CardDeck.begin());
				break;
			}
		}
		if (CheckSafeBoardPosition(PositionLeft, brd.mWidth, brd.mHeight))
		{
			BoardState::Slot& slt = brd.GetSlot(PositionLeft.x, PositionLeft.y);
			if (!slt.GetIsUsed() &&
				GetTopCard().GetRight() > u.GetCardReference()->GetLeft())
			{
				/*Set My Card Into Free Slot*/
				GetTopCard().SetPosition(slt.GetCardRectangle().left, slt.GetCardRectangle().top);
					
				/*Add Enemies Player Card To Board Card Deck*/
				brd.AddCard(GetTopCard(), slt);

				/*Take Primary Player Card*/
				u.ChangeOwner(BoardState::Slot::Owner::Enemy_Owned, u.GetCardReference());

				/*Set Win State To True*/
				mHasWon = true;

				/*Remove Card From Deck*/
				delete *CardDeck.begin();
				CardDeck.erase(CardDeck.begin());
				break;
			}
		}
		if (CheckSafeBoardPosition(PositionRight, brd.mWidth, brd.mHeight))
		{
			BoardState::Slot& slt = brd.GetSlot(PositionRight.x, PositionRight.y);
			if (!slt.GetIsUsed() &&
				GetTopCard().GetLeft() > u.GetCardReference()->GetRight())
			{
				/*Set My Card Into Free Slot*/
				GetTopCard().SetPosition(slt.GetCardRectangle().left, slt.GetCardRectangle().top);
					
				/*Add Enemies Player Card To Board Card Deck*/
				brd.AddCard(GetTopCard(), slt);

				/*Take Primary Player Card*/
				u.ChangeOwner(BoardState::Slot::Owner::Enemy_Owned, u.GetCardReference());

				/*Set Win State To True*/
				mHasWon = true;

				/*Remove Card From Deck*/
				delete *CardDeck.begin();
				CardDeck.erase(CardDeck.begin());
				break;
			}
		}
		
	}
	
	/*If No Win Then Handle Loss*/
	if (!mHasWon)
	{
		/*Set Range To Remaining Cards Available*/
		std::uniform_int_distribution<int> uni(0, CardDeck.size() - 1); // guaranteed unbiased

		for (auto& u : brd.GetSlots())
		{
			//Find Free Slot
			if (u.GetIsUsed())
				continue;

			const int p = uni(rng);

			/*Set My Card Into Free Slot*/
			(*CardDeck[p]).SetPosition(u.GetCardRectangle().left, u.GetCardRectangle().top);

			/*Add Enemies Player Card To Board Card Deck*/
			brd.AddCard((*CardDeck[p]), u);

			/*Remove Card From Deck*/
			delete *CardDeck.begin();
			CardDeck.erase(CardDeck.begin());

			/*Tell The Board Its Turn Over*/
			brd.ToogleTurn();
			break;
		}
	}
	
	CycleDeck();
	mCardIsDrawn = false;
	brd.ToogleTurn();

}

void Enemy::AddCard(float posx, float posy, std::string name, int U, int D, int L, int R)
{
	Card* aCard = new Card(posx, posy,
		name,
		U, D, L, R,
		mGameReference.GetCommonStore(),
		sf::IntRect(250, 300, 250, 300),
		Card::Owner::Enemy_Owned);
	CardDeck.push_back(aCard);
}

void Enemy::CycleDeck()
{
	if (CardDeck.size() == 0)
		return;

	AddCard(CardDeck.front()->GetPosition().x, CardDeck.front()->GetPosition().y,
		CardDeck.front()->GetName(),
		CardDeck.front()->GetUp(), CardDeck.front()->GetDown(), CardDeck.front()->GetLeft(), CardDeck.front()->GetRight());

	delete *CardDeck.begin();
	CardDeck.erase(CardDeck.begin());
}

Card& Enemy::GetTopCard()
{
	return (*CardDeck.front());
}

bool Enemy::CheckSafeBoardPosition(sf::Vector2i vec, int boardwidth, int boardheight)
{
	if (vec.x < 0)
	{
		return false;
	}
	else if (vec.x >= boardwidth)
	{
		return false;
	}
	else if (vec.y < 0)
	{
		return false;
	}
	else if (vec.y >= boardheight)
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
	mSprite.setTexture(mGameReference.GetCommonStore().GetTextureRef("EnemyPicture"));
	mSprite.setPosition(x, y);
	mName.setFont(mGameReference.GetCommonStore().GetFontRef("System"));
	mName.setString(name);

	/*Setup Card Back*/
	mCardBackSprite.setTexture(mGameReference.GetCommonStore().GetTextureRef("CardBack"));
	mCardBackSprite.setPosition(1620.0f, 50.0f);

	mName.setFillColor(sf::Color::Black);
	mName.setCharacterSize(18);
	mName.setPosition(x + mName_XOffset, y + mName_YOffset);
	AddCard(1520.0f, 150.0f, "Dragon", 3, 4, 3, 4);
	AddCard(1520.0f, 150.0f, "Planet", 3, 4, 3, 4);
	AddCard(1520.0f, 150.0f, "Gemini", 3, 4, 3, 4);
	AddCard(1520.0f, 150.0f, "Roadie", 3, 4, 3, 4);

	/*Set Initial Top Card Position*/
	CycleDeck();
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

	if (CardDeck.size() == 1 && !mCardIsDrawn)
	{
			mGameReference.GetWindow().draw(mCardBackSprite);
	}
	else if (CardDeck.size() > 1)
	{
		mGameReference.GetWindow().draw(mCardBackSprite);
	}
		

	/*Draw Top Card*/
	if (mCardIsDrawn)
		GetTopCard().Draw(mGameReference.GetWindow());
}
