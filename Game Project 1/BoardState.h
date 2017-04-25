#pragma once
#include "GameState.h"
#include "Enemy.h"
#include "Card.h"
class BoardState :
	public GameState
{
	enum TurnState {
		PlayerTurn,
		EnemyTurn
	};
	class Slot
	{
	public:
		Slot() = default;
		Slot(sf::FloatRect c, sf::FloatRect f)
		{
			CardRectangle = c;
			FullRectangle = f;
		}
		sf::FloatRect& GetCardRectangle() { return CardRectangle; }
		sf::FloatRect& GetFullRectangle() { return FullRectangle; }
		bool GetIsUsed() { return mIsUsed; }
		void ToogleUse();
	private:
		sf::FloatRect CardRectangle;
		sf::FloatRect FullRectangle;
		bool mIsUsed = false;
	};
public:
	/*Initiate Variables and Structures*/
	virtual void Initiate();
	/*The States Keyboard and Mouse Handling Function*/
	virtual void HandleInput();
	/*The States Logic Update Function*/
	virtual void Update(float dt);
	/*The States Draw Function*/
	virtual void Draw();
	/*Handle Events*/
	virtual void HandleEvents(sf::Event& ev);

	BoardState(Game& ref);
	~BoardState();

private:
	/*Setup Timer For Drawing Logic Of Selection Boarder*/
	bool mSelectSlotState = false;
	const float mSelectFlashTimer = 0.3f;
	float mSelectFlashCounter = 0.0f;
	bool mShowSelectBoarder = false;

	Game& mGameReference;
	sf::RectangleShape mBackgroundFill;
	sf::Sprite mBackgroundImage;
	sf::Sprite mSelectionBoarder;
	int mPlayerScore = 0;
	int mEnemyScore = 0;
	sf::Text mPlayerScoreText;
	sf::Text mEnemyScoreText;

	/*Track Turn*/
	TurnState mCurrentTurn = TurnState::PlayerTurn;
	
	/*Set Card Deck Selection Rectangles*/
	const sf::FloatRect mSelectCard_Player = { 200.0f, 200.0f, 250.0f, 300.0f };
	const sf::FloatRect mSelectCard_Enemy = { 1470.0f, 200.0f, 250.0f, 300.0f };

	/*Setup Board Selection Boarder Width*/
	const float mBOARDERWIDTH = 10.0f;

	/*Create Slot Array*/
	std::vector<Slot> mSlots;

	/*Create Board Card Deck*/
	std::vector<Card*> mBoardCardDeck;

	/*Create Board Card Position Rectangles Offset By Boarder Width*/
	const sf::FloatRect mSlot1 = { 535.0f - mBOARDERWIDTH, 50.0f - mBOARDERWIDTH, 250.0f, 300.0f };
	const sf::FloatRect mSlot2 = { 835.0f - mBOARDERWIDTH, 50.0f - mBOARDERWIDTH, 250.0f, 300.0f };
	const sf::FloatRect mSlot3 = { 1135.0f - mBOARDERWIDTH, 50.0f - mBOARDERWIDTH, 250.0f, 300.0f };
	const sf::FloatRect mSlot4 = { 535.0f - mBOARDERWIDTH, 400.0f - mBOARDERWIDTH, 250.0f, 300.0f };
	const sf::FloatRect mSlot5 = { 835.0f - mBOARDERWIDTH, 400.0f - mBOARDERWIDTH, 250.0f, 300.0f };
	const sf::FloatRect mSlot6 = { 1135.0f - mBOARDERWIDTH, 400.0f - mBOARDERWIDTH, 250.0f, 300.0f };
	const sf::FloatRect mSlot7 = { 535.0f - mBOARDERWIDTH, 750.0f - mBOARDERWIDTH, 250.0f, 300.0f };
	const sf::FloatRect mSlot8 = { 835.0f - mBOARDERWIDTH, 750.0f - mBOARDERWIDTH, 250.0f, 300.0f };
	const sf::FloatRect mSlot9 = { 1135.0f - mBOARDERWIDTH, 750.0f - mBOARDERWIDTH, 250.0f, 300.0f };
	
	/*Create Board Card Position Rectangles*/
	const sf::FloatRect mSlota = { 535.0f, 50.0f, 250.0f, 300.0f };
	const sf::FloatRect mSlotb = { 835.0f, 50.0f, 250.0f, 300.0f };
	const sf::FloatRect mSlotc = { 1135.0f, 50.0f, 250.0f, 300.0f };
	const sf::FloatRect mSlotd = { 535.0f, 400.0f, 250.0f, 300.0f };
	const sf::FloatRect mSlote = { 835.0f, 400.0f, 250.0f, 300.0f };
	const sf::FloatRect mSlotf = { 1135.0f, 400.0f, 250.0f, 300.0f };
	const sf::FloatRect mSlotg = { 535.0f, 750.0f, 250.0f, 300.0f };
	const sf::FloatRect mSloth = { 835.0f, 750.0f, 250.0f, 300.0f };
	const sf::FloatRect mSloti = { 1135.0f, 750.0f, 250.0f, 300.0f };
	
	/*Create Slots*/
	Slot A1 = { mSlota, mSlot1 };
	Slot A2 = { mSlotb, mSlot2 };
	Slot A3 = { mSlotc, mSlot3 };
	Slot B1 = { mSlotd, mSlot4 };
	Slot B2 = { mSlote, mSlot5 };
	Slot B3 = { mSlotf, mSlot6 };
	Slot C1 = { mSlotg, mSlot7 };
	Slot C2 = { mSloth, mSlot8 };
	Slot C3 = { mSloti, mSlot9 };

	Enemy mEnemy;
	bool mInitiated = false;
};

