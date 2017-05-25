#pragma once
#include "GameState.h"
#include "Enemy.h"
#include "Card.h"
#include <memory>

class BoardState :
	public GameState
{
	enum TurnState {
		PlayerTurn,
		EnemyTurn
	};
	enum WinState {
		PlayerWin,
		EnemyWin,
		Tie,
		GameRunning
	};
public:
	class Slot
	{
	public:
		enum Owner
		{
			Player_Owned,
			Enemy_Owned,
			None
		};
	public:
		Slot(float x, float y)
		{ 
			CardRectangle = { (float(x) * XINCREMENT) + INITIAL_X_OFFSET, 
				(float(y) * YINCREMENT) + INITIAL_Y_OFFSET, 
				SLOTWIDTH, 
				SLOTHEIGHT };
			FullRectangle = { (float(x) * XINCREMENT) + INITIAL_X_OFFSET_FULL, 
				(float(y) * YINCREMENT) + INITIAL_Y_OFFSET_FULL, 
				SLOTWIDTH, 
				SLOTHEIGHT };
			GridPosition.x = int(x);
			GridPosition.y = int(y);
		}
		const sf::FloatRect& GetCardRectangle() { return CardRectangle; }
		const sf::FloatRect& GetFullRectangle() { return FullRectangle; }
		const bool GetIsUsed() { return mIsUsed; }
		void ChangeOwner(Owner own, Card& card);
		const Owner GetOwner() { return mOwner; }
		const sf::Vector2i GetGridPosition() { return GridPosition; }
	private:
		/*Constants*/
		const float INITIAL_X_OFFSET = 535.0f;
		const float INITIAL_X_OFFSET_FULL = 525.0f;
		const float INITIAL_Y_OFFSET = 50.0f;
		const float INITIAL_Y_OFFSET_FULL = 40.0f;
		const float XINCREMENT = 300.0f;
		const float YINCREMENT = 350.0f;
		const float SLOTWIDTH = 250.0f;
		const float SLOTHEIGHT = 300.0f;

		sf::Vector2i GridPosition;
		sf::FloatRect CardRectangle;
		sf::FloatRect FullRectangle;
		Owner mOwner = Owner::None;
		bool mIsUsed = false;
	};
public:
	/*Constructors*/
	BoardState(Game& ref);
	~BoardState();
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

	/*Expose Boards Slots*/
	std::vector<Slot>& GetSlots() { return mSlots; }
	Slot& GetSlot(int x, int y);

	/*Slots Wide and Deep*/
	const int mWidth = 3;
	const int mHeight = 3;

	/*Change Turn*/
	void ToogleTurn();

	/*Increase Scores*/
	void PlayerScored() 
	{ mPlayerScore++; }
	void EnemyScored() 
	{ mEnemyScore++; }

	/*Expose Enemy*/
	Enemy& GetEnemy() { return mEnemy; }


private:
	/*Slot Boarder Flash Animation Timer*/
	bool mSelectSlotState = false;
	const float mSelectFlashTimer = 0.3f;
	float mSelectFlashCounter = 0.0f;
	bool mShowSelectBoarder = false;

	bool mIsTurning = false;
	const float mTurnWait = 1.0f;
	float mTurnCounter = 0.0f;

	Game& mGameReference;
	sf::RectangleShape mBackgroundFill;
	sf::Sprite mBackgroundImage;
	sf::Sprite mSelectionBoarder;
	sf::Sprite mBatButton;
	int mPlayerScore = 0;
	int mEnemyScore = 0;
	sf::Text mPlayerScoreText;
	sf::Text mEnemyScoreText;

	/*Track Turn*/
	TurnState mCurrentTurn = TurnState::PlayerTurn;
	
	/*Setup Board Selection Boarder Width*/
	const float mBOARDERWIDTH = 10.0f;

	/*Create Slot Array*/
	std::vector<Slot> mSlots;
	
	/*Create Slots - 2D Array*/
	Slot A1 = { 0, 0 };
	Slot A2 = { 1, 0 };
	Slot A3 = { 2, 0 };
	Slot B1 = { 0, 1 };
	Slot B2 = { 1, 1 };
	Slot B3 = { 2, 1 };
	Slot C1 = { 0, 2 };
	Slot C2 = { 1, 2 };
	Slot C3 = { 2, 2 };

	WinState mGameWinState = WinState::GameRunning;

	Enemy mEnemy;

	bool mInitiated = false;
};

