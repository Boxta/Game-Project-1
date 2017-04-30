#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "Card.h"
#include <random>

class BoardState;

class Enemy
{
public:
	Enemy(Game& ref);
	~Enemy();

	void Initiate(float x, float y,
		std::string name,
		float xn, float yn);
	void Update(const float dt);
	void Draw();
	Card& GetTopCard();
	void KillTopCard();
	void KillCard(int u);
	int GetDeckCount() { return CardDeck.size(); }
	void CycleDeck();
	void Turn(BoardState& brd);
	void ClearDeck();
private:
	sf::Vector2f mHandPositionA;
	void GetNewCards();
	Game& mGameReference;
	sf::Text mName;
	sf::Sprite mSprite;
	Card crd1;
	Card crd2;
	Card crd3;
	Card crd4;
	std::vector<Card*> CardDeck;
	std::vector<Card*>::iterator CardDeckIterator;
	int mCardDeckIterator = 0;
	bool CheckSafeBoardPosition(sf::Vector2i vec, int boardwidth, int boardheight);
	bool mIterateDirection = true;
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng;    // random-number engine used (Mersenne-Twister in this case)
};

