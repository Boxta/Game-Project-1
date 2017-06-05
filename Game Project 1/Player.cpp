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
	AddCard(445.0f, 40.0f, "P1", 5, 7, 3, 14);
	AddCard(445.0f, 40.0f, "Hello", 15, 7, 2, 2);
	AddCard(445.0f, 40.0f, "Card1", 2, 5, 13, 8);
	AddCard(445.0f, 40.0f, "Owch", 1, 6, 9, 4);
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

	/*Draw Top Card*/
	if(mCardIsDrawn)
		GetTopCard().Draw(mGameReference.GetWindow());

}

Card& Player::GetTopCard()
{
	return (*CardDeck.front());
}

Card& Player::GetCard(const sf::FloatRect id)
{
	for (auto U : CardDeck)
	{
		if ((*U).GetRectangle() == id)
		{
			return (*U);
		}
	}
}

void Player::CycleDeck()
{
	if (CardDeck.size() == 0)
		return;

	AddCard(CardDeck.front()->GetPosition().x, CardDeck.front()->GetPosition().y,
		CardDeck.front()->GetName(),
		CardDeck.front()->GetUp(), CardDeck.front()->GetDown(), CardDeck.front()->GetLeft(), CardDeck.front()->GetRight());
	
	delete *CardDeck.begin();
	CardDeck.erase(CardDeck.begin());

	mCardIsDrawn = true;
}

void Player::Turn(BoardState& brd, float xX, float yY)
{
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
			slt.GetCardReference()->GetDown() <
			GetTopCard().GetUp())
		{
			/*Win*/
			slt.ChangeOwner(BoardState::Slot::Owner::Player_Owned, slt.GetCardReference());
		}
		
	}
	if (CheckSafeBoardPosition(PositionDown, brd.mWidth, brd.mHeight))
	{
		/*Store Slot Ref*/
		BoardState::Slot& slt = brd.GetSlot(PositionDown.x, PositionDown.y);

		if (slt.GetIsUsed() &&
			slt.GetOwner() == BoardState::Slot::Owner::Enemy_Owned &&
			slt.GetCardReference()->GetUp() <
			GetTopCard().GetDown())
		{
			/*Win*/
			slt.ChangeOwner(BoardState::Slot::Owner::Player_Owned, slt.GetCardReference());
		}
		
	}
	if (CheckSafeBoardPosition(PositionLeft, brd.mWidth, brd.mHeight))
	{
		/*Store Slot Ref*/
		BoardState::Slot& slt = brd.GetSlot(PositionLeft.x, PositionLeft.y);

		if (slt.GetIsUsed() &&
			slt.GetOwner() == BoardState::Slot::Owner::Enemy_Owned &&
			slt.GetCardReference()->GetRight() <
			GetTopCard().GetLeft())
		{
			/*Win*/
			slt.ChangeOwner(BoardState::Slot::Owner::Player_Owned, slt.GetCardReference());
		}
		
	}
	if (CheckSafeBoardPosition(PositionRight, brd.mWidth, brd.mHeight))
	{
		/*Store Slot Ref*/
		BoardState::Slot& slt = brd.GetSlot(PositionRight.x, PositionRight.y);

		if (slt.GetIsUsed() &&
			slt.GetOwner() == BoardState::Slot::Owner::Enemy_Owned &&
			slt.GetCardReference()->GetLeft() <
			GetTopCard().GetRight())
		{
			/*Win*/
			slt.ChangeOwner(BoardState::Slot::Owner::Player_Owned, slt.GetCardReference());
		}
		
	}

	/*Set The Selected Slot and Card As Used*/
	brd.GetSlot(int(xX), int(yY)).ChangeOwner(BoardState::Slot::Owner::Player_Owned, &GetTopCard());

	/*Set Selected Card To Position Of The Slot*/
	GetTopCard().SetPosition(brd.GetSlot(int(xX), int(yY)).GetCardRectangle().left, brd.GetSlot(int(xX), int(yY)).GetCardRectangle().top);
		
	/*"Move" Selected Card To Board Deck*/
	brd.AddCard(GetTopCard(), brd.GetSlot(int(xX), int(yY)));

	/*Remove Card From Deck*/
	CardDeck.erase(CardDeck.begin());

	/*Ensure Next Card Isn't Drawn Immediately*/
	mCardIsDrawn = false;

	/*End Player Turn*/
	brd.ToogleTurn();
}

void Player::ClearDeck()
{
	CardDeck.clear();
}

void Player::AddCard(float posx, float posy, std::string name, int U, int D, int L, int R)
{
	Card* aCard = new Card(posx, posy,
		name,
		U, D, L, R,
		mGameReference.GetCommonStore(),
		sf::IntRect(0, 0, 250, 300),
		Card::Owner::Player_Owned );
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





