#include "Enemy.h"
#include "Game.h"


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

Card& Enemy::UseTopCard()
{
	Card& tmp = *CardDeck.back();
	tmp.ResetColor();
	CardDeck.pop_back();
	return tmp;
}

void Enemy::CycleDeck()
{

	CardDeckIterator = CardDeck.begin();
	Card* tmp = CardDeck.back();
	CardDeck.pop_back();
	CardDeck.insert(CardDeckIterator, tmp);
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

	crd1.Initiate(1620.0f, 50.0f, "Boss A");
	crd2.Initiate(1570.0f, 100.0f, "Boss B");
	crd3.Initiate(1520.0f, 150.0f, "Boss C");
	crd4.Initiate(1470.0f, 200.0f, "Boss D");
	
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
