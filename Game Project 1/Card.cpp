#include "Card.h"
#include "Game.h"

void Card::Initiate(float x, float y, std::string name)
{
	mName.setFont(mGameReference.GetCommonStore().GetFontRef("System"));
	mName.setString(name);
	mName.setPosition(x + 72, y + 50);
	mPosition = { x, y };
	mSprite.setTexture(mGameReference.GetCommonStore().GetTextureRef("TestCard"));
	mSprite.setPosition(x, y);
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(1, 8); // guaranteed unbiased
	mValue_Top = uni(rng);
	mValue_Down = uni(rng);
	mValue_Left = uni(rng);
	mValue_Right = uni(rng);
	mTextTop.setFont(mGameReference.GetCommonStore().GetFontRef("System"));
	mTextDown.setFont(mGameReference.GetCommonStore().GetFontRef("System"));
	mTextLeft.setFont(mGameReference.GetCommonStore().GetFontRef("System"));
	mTextRight.setFont(mGameReference.GetCommonStore().GetFontRef("System"));
	mTextTop.setString(std::to_string(mValue_Top));
	mTextDown.setString(std::to_string(mValue_Down));
	mTextLeft.setString(std::to_string(mValue_Left));
	mTextRight.setString(std::to_string(mValue_Right));
	mTextTop.setPosition(x + 117, y + 190);
	mTextDown.setPosition(x + 117, y + 230);
	mTextLeft.setPosition(x + 77, y + 210);
	mTextRight.setPosition(x + 157, y + 210);
	mRectangle.top = y;
	mRectangle.left = x;
	mRectangle.width = 250;
	mRectangle.height = 300;

}

void Card::Update(const float dt)
{
}

void Card::Draw()
{
	mGameReference.GetWindow().draw(mSprite);
	mGameReference.GetWindow().draw(mName);
	mGameReference.GetWindow().draw(mTextTop);
	mGameReference.GetWindow().draw(mTextDown);
	mGameReference.GetWindow().draw(mTextLeft);
	mGameReference.GetWindow().draw(mTextRight);

}

Card::Card(Game& ref)
	:
	mGameReference(ref)
{
	
}


Card::~Card()
{
}
