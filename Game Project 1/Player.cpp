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
}

void Player::Update(const float dt)
{
}

void Player::Draw()
{
	mGameReference.GetWindow().draw(mSprite);
	mGameReference.GetWindow().draw(mName);
	crd1.Draw();
	crd2.Draw();
	crd3.Draw();
	crd4.Draw();

}

Card& Player::GetClickedCard(sf::FloatRect& ref)
{
	if (crd1.GetRectangle() == ref)
	{
		return crd1;
	}
	else if (crd2.GetRectangle() == ref)
	{
		return crd2;
	}
	else if (crd3.GetRectangle() == ref)
	{
		return crd3;
	}
	else if (crd4.GetRectangle() == ref)
	{
		return crd4;
	}
}
