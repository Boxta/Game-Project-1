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
	mSprite.setTexture(mGameReference.GetCommonStore().GetTextureRef("PlayerPicture"));
	mSprite.setPosition(x, y);
	mName.setFont(mGameReference.GetCommonStore().GetFontRef("System"));
	mName.setString(name);
	mName.setPosition(xn, yn);
	mName.setFillColor(sf::Color::Black);
	mName.setCharacterSize(18);

	crd1.Initiate(50.0f, 50.0f, "Card A");
	crd2.Initiate(100.0f, 100.0f, "Card B");
	crd3.Initiate(150.0f, 150.0f, "Card C");
	crd4.Initiate(200.0f, 200.0f, "Card D");

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
	mGameReference.GetWindow().draw(mSprite);
	mGameReference.GetWindow().draw(mName);
	for (int p = 0; p < CardDeck.size(); p++)
	{
		CardDeck[p]->SetPosition((p + 1) * 50, ((p + 1) * 50));
		CardDeck[p]->Draw();
	}
}

Card& Player::GetTopCard()
{
	return *CardDeck.back();
}

Card& Player::UseTopCard()
{
	Card& tmp = *CardDeck.back();
	tmp.ResetColor();
	CardDeck.pop_back();
	return tmp;
}

void Player::CycleDeck()
{

	CardDeckIterator = CardDeck.begin();
	Card* tmp = CardDeck.back();
	CardDeck.pop_back();
	CardDeck.insert(CardDeckIterator, tmp);
}


