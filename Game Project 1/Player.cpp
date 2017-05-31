#include "Player.h"
#include "Game.h"
#include "BoardState.h"

Player::Player(Game& ref)
	:
mGameReference(ref),
rng(rd())
{
}

Player::~Player()
{
}

void Player::Initiate(float x, float y, 
	std::string name)
{
	mHandPositionA = { 140.0f, 150.0f };

	/*Setup Player Sprite*/
	mSprite.setTexture(mGameReference.GetCommonStore().GetTextureRef("PlayerPicture"));
	mSprite.setPosition(x, y);

	/*Setup Player Name*/
	mName.setFont(mGameReference.GetCommonStore().GetFontRef("System"));
	mName.setString(name);
	mName.setFillColor(sf::Color::Black);
	mName.setCharacterSize(18);
	mName.setPosition(x + mName_XOffset, y + mName_YOffset);

	/*Setup Card Back*/
	mCardBackSprite.setTexture(mGameReference.GetCommonStore().GetTextureRef("CardBack"));
	mCardBackSprite.setPosition(50.0f, 50.0f);

	/*Create Player Cards*/
	AddCard(0.0f, 0.0f, "P1", 5, 7, 3, 14);
	AddCard(0.0f, 0.0f, "Hello", 15, 7, 2, 2);
	AddCard(0.0f, 0.0f, "Card1", 2, 5, 13, 8);
	AddCard(0.0f, 0.0f, "Owch", 1, 6, 9, 4);

	/*Set Initial Top Card Position*/
	GetTopCard().SetPosition(250.0f, 150.0f);
}

void Player::Update(const float dt)
{
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

	/*Draw Card Back*/
	mGameReference.GetWindow().draw(mCardBackSprite);

	/*Draw Top Card*/
	GetTopCard().Draw(mGameReference.GetWindow());

	/*Draw Player Cards In Deck
	for (unsigned int T = 0; T < CardDeck.size(); T++)
	{
		if (T < mCardDeckIterator &&
			CardDeck[T].GetState() != Card::CardState::Used)
		{
			CardDeck[T].SetPosition(mHandPositionA.x - 125.0f, mHandPositionA.y - 80.0f);
			CardDeck[T].Draw(mGameReference.GetWindow());
		}
	}
	for (unsigned int T = 0; T < CardDeck.size(); T++)
	{
		if (T > mCardDeckIterator &&
			CardDeck[T].GetState() != Card::CardState::Used)
		{
			CardDeck[T].SetPosition(mHandPositionA.x + 125.0f, mHandPositionA.y - 80.0f);
			CardDeck[T].Draw(mGameReference.GetWindow());
		}
	}
	for (unsigned int T = 0; T < CardDeck.size(); T++)
	{
		if (T == mCardDeckIterator &&
			CardDeck[T].GetState() != Card::CardState::Used)
		{
			CardDeck[mCardDeckIterator].SetPosition(mHandPositionA.x, mHandPositionA.y);
			CardDeck[mCardDeckIterator].Draw(mGameReference.GetWindow());
		}
	}*/
	
	/*Draw Used Cards On Board*/
	for (unsigned int T = 0; T < CardDeck.size(); T++)
	{
		if (CardDeck[T].GetState() == Card::CardState::Used)
		{
			CardDeck[T].Draw(mGameReference.GetWindow());
		}
	}
}

Card& Player::GetTopCard()
{
	return CardDeck.front();
}

Card& Player::GetCard(const sf::FloatRect id)
{
	for (auto& U : CardDeck)
	{
		if (U.GetRectangle() == id)
		{
			return U;
		}
	}
}

void Player::CycleDeck()
{
	Card temp = GetTopCard();
	CardDeck.erase(CardDeck.begin());
	CardDeck.push_back(temp);
	GetTopCard().SetPosition(250.0f, 150.0f);
}

void Player::Turn(BoardState& brd, float xX, float yY)
{
	/*Mark The Slots Card As Used*/
	brd.GetSlot(int(xX), int(yY)).ChangeOwner(BoardState::Slot::Owner::Player_Owned);

	/*Set Slots Card To Position Of The Slot*/
	GetTopCard().SetPosition(brd.GetSlot(int(xX), int(yY)).GetCardRectangle().left, brd.GetSlot(int(xX), int(yY)).GetCardRectangle().top);
	
	/*Board Card Deck Iterators*/
	std::vector<Card*>::iterator iterator, end;
	
	//Store Postion and Potential surrounding slot positions of the slot/card
	const sf::Vector2i DeckCardPosition = { int(brd.GetSlot(int(xX), int(yY)).GetGridPosition().x), int(brd.GetSlot(int(xX), int(yY)).GetGridPosition().y) };
	const sf::Vector2i PositionAbove = sf::Vector2i(DeckCardPosition.x, DeckCardPosition.y - 1);
	const sf::Vector2i PositionDown = sf::Vector2i(DeckCardPosition.x, DeckCardPosition.y + 1);
	const sf::Vector2i PositionLeft = sf::Vector2i(DeckCardPosition.x - 1, DeckCardPosition.y);
	const sf::Vector2i PositionRight = sf::Vector2i(DeckCardPosition.x + 1, DeckCardPosition.y);

	/*Check Surrounding Slots For Enemy Cards and Test/Execute A Win*/
	if (CheckSafeBoardPosition(PositionAbove, brd.mWidth, brd.mHeight))
	{
		/*Store Slot Ref*/
		BoardState::Slot& slt = brd.GetSlot(PositionAbove.x, PositionAbove.y);

		for(iterator = brd.GetCardDeck().begin(), end = brd.GetCardDeck().end(); iterator != end; ++iterator)
		{
			if ((*iterator)->GetRectangle() == slt.GetCardRectangle() &&
				slt.GetIsUsed() &&
				slt.GetOwner() == BoardState::Slot::Owner::Enemy_Owned &&
				(*iterator)->GetDown() <
				GetTopCard().GetUp())
			{
				/*Win*/
				slt.ChangeOwner(BoardState::Slot::Owner::Player_Owned);
			}
		}
	}
	if (CheckSafeBoardPosition(PositionDown, brd.mWidth, brd.mHeight))
	{
		/*Store Slot Ref*/
		BoardState::Slot& slt = brd.GetSlot(PositionDown.x, PositionDown.y);

		for (iterator = brd.GetCardDeck().begin(), end = brd.GetCardDeck().end(); iterator != end; ++iterator)
		{
			if ((*iterator)->GetRectangle() == slt.GetCardRectangle() &&
				slt.GetIsUsed() &&
				slt.GetOwner() == BoardState::Slot::Owner::Enemy_Owned &&
				(*iterator)->GetUp() <
				GetTopCard().GetDown())
			{
				/*Win*/
				slt.ChangeOwner(BoardState::Slot::Owner::Player_Owned);
			}
		}
	}
	if (CheckSafeBoardPosition(PositionLeft, brd.mWidth, brd.mHeight))
	{
		/*Store Slot Ref*/
		BoardState::Slot& slt = brd.GetSlot(PositionLeft.x, PositionLeft.y);

		for (iterator = brd.GetCardDeck().begin(), end = brd.GetCardDeck().end(); iterator != end; ++iterator)
		{
			if ((*iterator)->GetRectangle() == slt.GetCardRectangle() &&
				slt.GetIsUsed() &&
				slt.GetOwner() == BoardState::Slot::Owner::Enemy_Owned &&
				(*iterator)->GetRight() <
				GetTopCard().GetLeft())
			{
				/*Win*/
				slt.ChangeOwner(BoardState::Slot::Owner::Player_Owned);
			}
		}
	}
	if (CheckSafeBoardPosition(PositionRight, brd.mWidth, brd.mHeight))
	{
		/*Store Slot Ref*/
		BoardState::Slot& slt = brd.GetSlot(PositionRight.x, PositionRight.y);

		for (iterator = brd.GetCardDeck().begin(), end = brd.GetCardDeck().end(); iterator != end; ++iterator)
		{
			if ((*iterator)->GetRectangle() == slt.GetCardRectangle() &&
				slt.GetIsUsed() &&
				slt.GetOwner() == BoardState::Slot::Owner::Enemy_Owned &&
				(*iterator)->GetLeft() <
				GetTopCard().GetRight())
			{
				/*Win*/
				slt.ChangeOwner(BoardState::Slot::Owner::Player_Owned);
			}
		}
	}
		
	/*"Move" Selected Card To Board Deck*/
	brd.AddCard(GetTopCard(), brd.GetSlot(int(xX), int(yY)));

	/*Remove Card From Deck*/
	CardDeck.erase(CardDeck.begin());

	/*End Player Turn*/
	brd.ToogleTurn();
}

void Player::ClearDeck()
{
	CardDeck.clear();
}

void Player::AddCard(float posx, float posy, std::string name, int U, int D, int L, int R)
{
	Card aCard = { posx, posy,
		name,
		U, D, L, R,
		mGameReference.GetCommonStore(),
		sf::IntRect(0, 0, 250, 300),
		Card::Owner::Player_Owned };
	CardDeck.push_back(aCard);
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





