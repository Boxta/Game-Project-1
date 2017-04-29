#include "Player.h"
#include "Game.h"


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
	mHandPositionA = { 140.0f, 100.0f };
	mHandPositionB = { 10.0f, 80.0f };
	mHandPositionC = { 270.0f, 80.0f };

	mSprite.setTexture(mGameReference.GetCommonStore().GetTextureRef("PlayerPicture"));
	mSprite.setPosition(x, y);
	mName.setFont(mGameReference.GetCommonStore().GetFontRef("System"));
	mName.setString(name);
	mName.setPosition(xn, yn);
	mName.setFillColor(sf::Color::Black);
	mName.setCharacterSize(18);

	crd1.Initiate(140.0f, 100.0f, "Card A", Card::CardOwner::Player_Owned);
	crd2.Initiate(100.0f, 100.0f, "Card B", Card::CardOwner::Player_Owned);
	crd3.Initiate(150.0f, 150.0f, "Card C", Card::CardOwner::Player_Owned);
	crd4.Initiate(200.0f, 200.0f, "Card D", Card::CardOwner::Player_Owned);

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

Card& Player::GetTopCard()
{
	return *CardDeck[mCardDeckIterator];
}


void Player::CycleDeck()
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

void Player::KillTopCard()
{
	CardDeck.erase(CardDeck.begin() + mCardDeckIterator);
}





