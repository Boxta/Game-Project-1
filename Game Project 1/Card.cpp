#include "Card.h"

void Card::Draw(sf::RenderWindow& wnd)
{
	wnd.draw(mSprite);
	wnd.draw(mName);
	wnd.draw(mTextTop);
	wnd.draw(mTextDown);
	wnd.draw(mTextLeft);
	wnd.draw(mTextRight);
}

void Card::SetDrawRectangle(sf::IntRect rect)
{
	mSprite.setTextureRect(rect);
}



Card::Card(float positionx, float positiony, 
	std::string name, 
	int U, 
	int D, 
	int L, 
	int R, 
	CmnStore & st, 
	sf::IntRect texrect,
	Owner own)
	:
	mValue_Top(U),
	mValue_Down(D),
	mValue_Left(L),
	mValue_Right(R),
	mOwner(own)
{
	/*Set Card Recatangle*/
	mRectangle.left = positionx;
	mRectangle.top = positiony;
	mRectangle.width = 250;
	mRectangle.height = 300;

	/*Set Texture Y Value*/
	mTextureYValue = texrect.top;

	/*Setup Card Name*/
	mName.setFont(st.GetFontRef("System"));
	mName.setString(name);
	mName.setCharacterSize(18);

	/*Setup Card Sprite*/
	mSprite.setTexture(st.GetTextureRef("TestCard"));
	mSprite.setTextureRect(texrect);

	/*Setup Card Value Text*/
	mTextTop.setFont(st.GetFontRef("System"));
	mTextDown.setFont(st.GetFontRef("System"));
	mTextLeft.setFont(st.GetFontRef("System"));
	mTextRight.setFont(st.GetFontRef("System"));
	mTextTop.setCharacterSize(22);
	mTextDown.setCharacterSize(22);
	mTextLeft.setCharacterSize(22);
	mTextRight.setCharacterSize(22);

	/*Assign Card Values to Value Text'*/
	mTextTop.setString(std::to_string(mValue_Top));
	mTextDown.setString(std::to_string(mValue_Down));
	mTextLeft.setString(std::to_string(mValue_Left));
	mTextRight.setString(std::to_string(mValue_Right));

	/*Set Positions*/
	SetPosition(positionx, positiony);
}


Card::~Card()
{
}

void Card::SetPosition(float x, float y)
{
	mRectangle.top = y;
	mRectangle.left = x;

	const float CardMiddle = (mRectangle.left + (mRectangle.width / 2));
	const float LeftRightValueSpace = 10.0f;
	
	/*Set Name Position*/
	mName.setPosition((mRectangle.left + (mRectangle.width / 2) - (mName.getLocalBounds().width / 2)), y + mName_YOffset);
	
	/*Set Sprite Position*/
	mSprite.setPosition(x, y);
	
	/*Set Text Position*/
	mTextTop.setPosition(CardMiddle - (mTextTop.getLocalBounds().width / 2), y + 206.0f);
	mTextDown.setPosition(CardMiddle - (mTextDown.getLocalBounds().width / 2), y + 248.0f);
	mTextLeft.setPosition(CardMiddle - (mTextLeft.getLocalBounds().width + LeftRightValueSpace), y + 227.0f);
	mTextRight.setPosition(CardMiddle + LeftRightValueSpace, y + 227.0f);
}

void Card::ChangeOwner(Owner own)
{
	switch (own)
	{
	case Owner::None:
		mOwner = Owner::None;
		break;
	case Owner::Player_Owned:
		SetDrawRectangle(sf::IntRect(0, mTextureYValue, 250, 300));
		mOwner = Owner::Player_Owned;
		break;
	case Owner::Enemy_Owned:
		SetDrawRectangle(sf::IntRect(250, mTextureYValue, 250, 300));
		mOwner = Owner::Enemy_Owned;
		break;
	}
}






