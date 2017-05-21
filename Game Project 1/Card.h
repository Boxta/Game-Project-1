#pragma once
#include <SFML\Graphics.hpp>
#include "CmnStore.h"

class Game;

class Card
{
public:
	enum CardState
	{
		Selected,
		Free,
		Used
	};
	enum Owner
	{
		Player_Owned,
		Enemy_Owned,
		None
	};
public:
	/*Constructors*/
	Card(float positionx, float positiony,
		std::string name,
		int U,
		int D,
		int L,
		int R,
		CmnStore& st,
		sf::IntRect texrect
	);
	~Card();
	
	/*Draw Card*/
	void Draw(sf::RenderWindow& wnd);
	void SetDrawRectangle(sf::IntRect rect);
	
	/*Get Rectangle*/
	const sf::FloatRect& GetRectangle() { return mRectangle; }
	
	/*Get and Set State*/
	const CardState GetState() { return mState; }
	void SetState(CardState st) { mState = st; }

	/*Set Position*/
	void SetPosition(float x, float y); 
	/*Get Position*/
	const sf::Vector2i GetPosition() { sf::Vector2i{ int(GetRectangle().left), int(GetRectangle().top) }; }

	/*Get Values*/
	const int GetUp() { return mValue_Top; }
	const int GetDown() { return mValue_Down; }
	const int GetLeft() { return mValue_Left; }
	const int GetRight() { return mValue_Right; }

	/*Ownership Functions*/
	void ChangeOwner(Owner own);
	const Owner GetOwner() { return mOwner; }

private:
	/*Card Values*/
	Owner mOwner = Owner::None;
	int mValue_Top = 0;
	int mValue_Left = 0;
	int mValue_Right = 0;
	int mValue_Down = 0;
	CardState mState = CardState::Free;
	sf::FloatRect mRectangle;
	sf::Sprite mSprite;
	sf::Text mName;
	float mName_YOffset = 5.0f;
	sf::Text mTextTop;						
	sf::Text mTextDown;
	sf::Text mTextLeft;
	sf::Text mTextRight;
	int mTextureYValue = 0;
};

