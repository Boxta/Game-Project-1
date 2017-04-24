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
}

void Enemy::Update(const float dt)
{
}

void Enemy::Draw()
{
	mGameReference.GetWindow().draw(mSprite);
	mGameReference.GetWindow().draw(mName);
	crd1.Draw();
	crd2.Draw();
	crd3.Draw();
	crd4.Draw();

}
