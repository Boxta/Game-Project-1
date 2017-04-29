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
public:
	class Slot
	{
	public:
		Slot() = default;
		Slot(int x, int y)
		{ 
			mBoardPosition.x = x;
			mBoardPosition.y = y;
			CardRectangle = { (float(x) * 300.0f) + 535.0f, (float(y) * 350.0f) + 50.0f, 250.0f, 300.0f };
			FullRectangle = { (float(x) * 300.0f) + 525.0f, (float(y) * 350.0f) + 40.0f, 250.0f, 300.0f };
		}
		sf::Vector2i mBoardPosition;
		sf::FloatRect& GetCardRectangle() { return CardRectangle; }
		sf::FloatRect& GetFullRectangle() { return FullRectangle; }
		bool GetIsUsed() { return mIsUsed; }
		void ToogleUse();
		Card* mCard;
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

	/*Expose Boards Card Deck and Slots*/
	std::vector<Slot>& GetSlots() { return mSlots; }
	Slot& GetSlot(int x, int y);
	/*Slot Width and Height*/
	const int mWidth = 3;
	const int mHeight = 3;

	void ToogleTurn();
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
	
	/*Setup Board Selection Boarder Width*/
	const float mBOARDERWIDTH = 10.0f;

	/*Create Slot Array*/
	std::vector<Slot> mSlots;

	/*Create Board Cards*/
	Card Card_A1;
	Card Card_A2;
	Card Card_A3;
	Card Card_B1;
	Card Card_B2;
	Card Card_B3;
	Card Card_C1;
	Card Card_C2;
	Card Card_C3;
	
	/*Create Slots*/
	Slot A1 = { 0, 0 };
	Slot A2 = { 1, 0 };
	Slot A3 = { 2, 0 };
	Slot B1 = { 0, 1 };
	Slot B2 = { 1, 1 };
	Slot B3 = { 2, 1 };
	Slot C1 = { 0, 2 };
	Slot C2 = { 1, 2 };
	Slot C3 = { 2, 2 };


	Enemy mEnemy;
	bool mInitiated = false;
};

