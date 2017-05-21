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

	mSprite.setTexture(mGameReference.GetCommonStore().GetTextureRef("PlayerPicture"));
	mSprite.setPosition(x, y);
	mName.setFont(mGameReference.GetCommonStore().GetFontRef("System"));
	mName.setString(name);
	mName.setFillColor(sf::Color::Black);
	mName.setCharacterSize(18);
	mName.setPosition(x + mName_XOffset, y + mName_YOffset);
	AddCard(0.0f, 0.0f, "P1", 9, 9, 18, 14);
	AddCard(0.0f, 0.0f, "Hello", 5, 5, 5, 5);
	AddCard(0.0f, 0.0f, "Card1", 13, 1, 1, 1);
	AddCard(0.0f, 0.0f, "Owch", 13, 14, 13, 4);
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

	/*Draw Player Cards In Deck*/
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
	}
	
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
	return CardDeck[mCardDeckIterator];
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

void Player::Turn(BoardState& brd, float xX, float yY)
{
	/*Mark The Slots Card As Used*/
	brd.GetSlot(int(xX), int(yY)).ChangeOwner(BoardState::Slot::Owner::Player_Owned, GetTopCard());

	/*Set Slots Card To Position Of The Slot*/
	GetTopCard().SetPosition(brd.GetSlot(int(xX), int(yY)).GetCardRectangle().left, brd.GetSlot(int(xX), int(yY)).GetCardRectangle().top);
	GetTopCard().SetState(Card::CardState::Used);

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
				
		if (slt.GetIsUsed() &&
			slt.GetOwner() == BoardState::Slot::Owner::Enemy_Owned &&
			brd.GetEnemy().GetCard(slt.GetCardRectangle()).GetDown() < 
			GetTopCard().GetUp())
		{
			/*Win*/
			slt.ChangeOwner(BoardState::Slot::Owner::Player_Owned, brd.GetEnemy().GetCard(slt.GetCardRectangle()));
		}
	}
	if (CheckSafeBoardPosition(PositionDown, brd.mWidth, brd.mHeight))
	{
		BoardState::Slot& slt = brd.GetSlot(PositionDown.x, PositionDown.y);

		if (slt.GetIsUsed() &&
			slt.GetOwner() == BoardState::Slot::Owner::Enemy_Owned &&
			brd.GetEnemy().GetCard(slt.GetCardRectangle()).GetUp() < 
			GetTopCard().GetDown())
		{
			/*Win*/
			slt.ChangeOwner(BoardState::Slot::Owner::Player_Owned, brd.GetEnemy().GetCard(slt.GetCardRectangle()));
		}
	}
	if (CheckSafeBoardPosition(PositionLeft, brd.mWidth, brd.mHeight))
	{
		BoardState::Slot& slt = brd.GetSlot(PositionLeft.x, PositionLeft.y);

		if (slt.GetIsUsed() &&
			slt.GetOwner() == BoardState::Slot::Owner::Enemy_Owned &&
			brd.GetEnemy().GetCard(slt.GetCardRectangle()).GetRight() < 
			GetTopCard().GetLeft())
		{
			/*Win*/
			slt.ChangeOwner(BoardState::Slot::Owner::Player_Owned, brd.GetEnemy().GetCard(slt.GetCardRectangle()));
		}
	}
	if (CheckSafeBoardPosition(PositionRight, brd.mWidth, brd.mHeight))
	{
		BoardState::Slot& slt = brd.GetSlot(PositionRight.x, PositionRight.y);

		if (slt.GetIsUsed() &&
			slt.GetOwner() == BoardState::Slot::Owner::Enemy_Owned &&
			brd.GetEnemy().GetCard(slt.GetCardRectangle()).GetLeft() < 
			GetTopCard().GetRight())
		{
			/*Win*/
			slt.ChangeOwner(BoardState::Slot::Owner::Player_Owned, brd.GetEnemy().GetCard(slt.GetCardRectangle()));
		}
	}

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
		sf::IntRect(0, 0, 250, 300) };
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





