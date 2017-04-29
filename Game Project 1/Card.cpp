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
	mName.setPosition(x + 72, y + 50);
	
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
	
	/*Assign Card Values to Value Text'*/
	mTextTop.setString(std::to_string(mValue_Top));
	mTextDown.setString(std::to_string(mValue_Down));
	mTextLeft.setString(std::to_string(mValue_Left));
	mTextRight.setString(std::to_string(mValue_Right));

	/*Set Text Position*/
	int TopSize = int(mTextTop.getLocalBounds().width);
	int DownSize = int(mTextDown.getLocalBounds().width);
	int LeftSize = int(mTextLeft.getLocalBounds().width);
	int RightSize = int(mTextRight.getLocalBounds().width);

	mTextTop.setPosition((x + (mRectangle.width / 2)) - (TopSize / 2), y + 184);
	mTextDown.setPosition((x + (mRectangle.width / 2)) - (DownSize / 2), y + 236);
	mTextLeft.setPosition((x + (mRectangle.width / 2)) - 40 - (LeftSize / 2), y + 210);
	mTextRight.setPosition((x + (mRectangle.width / 2)) + 40 - (RightSize / 2), y + 210);
}

void Card::Update(const float dt)
{
	/*Keep Asset Positions Aligned To Object Position*/
	/*Set Card Recatangle*/

	switch (mState)
	{
	case CardState::Free:
		mSprite.setColor(sf::Color::White);
		break;
	case CardState::Selected:
		mSprite.setColor(sf::Color::Color(100, 0, 0, 255));
		break;
	case CardState::Used:
		mSprite.setColor(sf::Color::White);
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
	mName.setPosition(x + 72, y + 50);
	
	/*Set Sprite Position*/
	mSprite.setPosition(x, y);
	
	/*Set Text Position*/
	int TopSize = int(mTextTop.getLocalBounds().width);
	int DownSize = int(mTextDown.getLocalBounds().width);
	int LeftSize = int(mTextLeft.getLocalBounds().width);
	int RightSize = int(mTextRight.getLocalBounds().width);

	mTextTop.setPosition((x + (mRectangle.width / 2)) - (TopSize / 2), y + 184);
	mTextDown.setPosition((x + (mRectangle.width / 2)) - (DownSize / 2), y + 236);
	mTextLeft.setPosition((x + (mRectangle.width / 2)) - 40 - (LeftSize / 2), y + 210);
	mTextRight.setPosition((x + (mRectangle.width / 2)) + 40 - (RightSize / 2), y + 210);
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


