#include "Card.h"
#include "Game.h"

void Card::Initiate(float x, float y, std::string name, CardOwner own)
{
	/*Set Owner*/
	mOwner = own;

	/*Set Card Recatangle*/
	mRectangle.top = y;
	mRectangle.left = x;
	mRectangle.width = 250;
	mRectangle.height = 300;

	/*Setup Card Name*/
	mName.setFont(mGameReference.GetCommonStore().GetFontRef("System"));
	mName.setString(name);
	mName.setCharacterSize(22);
	mName.setPosition(x + ((mName.getString().getSize() * mName.getCharacterSize()) / 2) + 20.0f, y - 4);
	float u = mName.getString().getSize();
	float t = mName.getCharacterSize();
	/*Setup Card Position*/
	mPosition = { x, y };
	
	/*Setup Card Sprite*/
	mSprite.setTexture(mGameReference.GetCommonStore().GetTextureRef("TestCard"));
	mSprite.setPosition(x, y);

	/*Setup Random Generator*/
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(1, 9); // guaranteed unbiased
	
	/*Setup Card Values*/
	mValue_Top = uni(rng);
	mValue_Down = uni(rng);
	mValue_Left = uni(rng);
	mValue_Right = uni(rng);

	/*Setup Card Value Text*/
	mTextTop.setFont(mGameReference.GetCommonStore().GetFontRef("System"));
	mTextDown.setFont(mGameReference.GetCommonStore().GetFontRef("System"));
	mTextLeft.setFont(mGameReference.GetCommonStore().GetFontRef("System"));
	mTextRight.setFont(mGameReference.GetCommonStore().GetFontRef("System"));
	mTextTop.setCharacterSize(22);
	mTextDown.setCharacterSize(22);
	mTextLeft.setCharacterSize(22);
	mTextRight.setCharacterSize(22);
	
	/*Assign Card Values to Value Text'*/
	mTextTop.setString(std::to_string(mValue_Top));
	mTextDown.setString(std::to_string(mValue_Down));
	mTextLeft.setString(std::to_string(mValue_Left));
	mTextRight.setString(std::to_string(mValue_Right));

	/*Set Text Position*/
	SetPosition(x, y);

}

void Card::Update(const float dt)
{
	/*Keep Asset Positions Aligned To Object Position*/
	/*Set Card Recatangle*/
	switch (mState)
	{
	case CardState::Free:
		break;
	case CardState::Selected:
		break;
	case CardState::Used:
		break;
	default:
		break;
	}

	switch (mOwner)
	{
	case CardOwner::Player_Owned:
		mSprite.setTextureRect(sf::IntRect(0, 0, 250, 300));
		break;
	case CardOwner::Enemy_Owned:
		mSprite.setTextureRect(sf::IntRect(250, 0, 250, 300));
		break;
	default:
		break;
	}
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

void Card::SetPosition(float x, float y)
{
	mPosition.x = x; 
	mPosition.y = y; 

	mRectangle.top = y;
	mRectangle.left = x;
	
	/*Set Name Position*/
	mName.setPosition(x + ((mName.getString().getSize() * mName.getCharacterSize()) / 2) + 20.0f, y + 4.0f);
	
	/*Set Sprite Position*/
	mSprite.setPosition(x, y);
	
	/*Set Text Position*/
	float TopSize = mTextTop.getLocalBounds().width;
	float DownSize = mTextDown.getLocalBounds().width;
	float LeftSize = mTextLeft.getLocalBounds().width;
	float RightSize = mTextRight.getLocalBounds().width;

	mTextTop.setPosition((x + (mRectangle.width / 2)) + 3.0f - (TopSize / 2.0f), y + 206.0f);
	mTextDown.setPosition((x + (mRectangle.width / 2)) + 3.0f - (DownSize / 2.0f), y + 248.0f);
	mTextLeft.setPosition((x + (mRectangle.width / 2)) - 17.0f - (LeftSize / 2.0f), y + 227.0f);
	mTextRight.setPosition((x + (mRectangle.width / 2)) + 23.0f - (RightSize / 2.0f), y + 227.0f);
}

void Card::CopyCard(Card& ref)
{
	ref.mValue_Top = mValue_Top;
	ref.mValue_Left = mValue_Left;
	ref.mValue_Right = mValue_Right;
	ref.mValue_Down = mValue_Down;

	ref.mState = mState;
	ref.mRectangle = mRectangle;
	
	ref.mPosition = mPosition;
	ref.mSprite = mSprite;
	ref.mName = mName;
	ref.mTextTop = mTextTop;
	ref.mTextDown = mTextDown;
	ref.mTextLeft = mTextLeft;
	ref.mTextRight = mTextRight;
	ref.mOwner = mOwner;
}




