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
		std::string name);
	void Update(const float dt);
	void Draw();
	Card& GetTopCard();
	Card& GetCard(const sf::FloatRect id);
	void KillCard(int u);
	int GetDeckCount() { return CardDeck.size(); }
	void CycleDeck();
	void Turn(BoardState& brd);
	void ClearDeck();
	std::vector<Card>& GetDeck() { return CardDeck; }
	void AddCard(float posx, float posy, std::string name, int U, int D, int L, int R);
private:
	sf::Vector2f mHandPositionA;
	Game& mGameReference;
	sf::Text mName;
	const float mName_XOffset = 80.0f;
	const float mName_YOffset = 20.0f;
	sf::Sprite mSprite;
	std::vector<Card> CardDeck;
	std::vector<Card>::iterator CardDeckIterator;
	Card& GetWorstCard();
	int mCardDeckIterator = 0;
	bool CheckSafeBoardPosition(sf::Vector2i vec, int boardwidth, int boardheight);
	bool mIterateDirection = true;
	std::random_device rd;     
	std::mt19937 rng;
};

