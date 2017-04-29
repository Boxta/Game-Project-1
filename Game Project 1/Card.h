#pragma once
#include <SFML\Graphics.hpp>
#include <random>
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
	enum CardOwner
	{
		Player_Owned,
		Enemy_Owned
	};
public:
	void Initiate(float x, float y, std::string name, CardOwner own);
	void Update(const float dt);
	void Draw();
	Card() = default;
	Card(Game& ref);
	~Card();
	sf::FloatRect& GetRectangle() { return mRectangle; }

	/*Used to toggle color when card has been "selected" by player*/
	void SetState(CardState st) { mState = st; }

	CardState GetState() { return mState; }
	void SetPosition(float x, float y); 

	int mValue_Top = 0;
	int mValue_Left = 0;
	int mValue_Right = 0;
	int mValue_Down = 0;
	void SetSmallDraw(bool ison);
	CardOwner GetOwner() { return mOwner; }
	void CopyCard(Card& ref);
private:
	CardState mState = CardState::Free;
	sf::FloatRect mRectangle;
	Game& mGameReference;
	sf::Vector2f mPosition;
	sf::Sprite mSprite;
	sf::Text mName;
	sf::Text mTextTop;
	sf::Text mTextDown;
	sf::Text mTextLeft;
	sf::Text mTextRight;
	CardOwner mOwner;
	std::random_device rd;     // only used once to initialise (seed) engine
};

