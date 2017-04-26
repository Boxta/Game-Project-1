#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "Card.h"

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
	Card& UseTopCard();
	int GetDeckCount() { return CardDeck.size(); }
	void CycleDeck();
	void Turn(BoardState& brd);
private:
	Game& mGameReference;
	sf::Text mName;
	sf::Sprite mSprite;
	Card crd1;
	Card crd2;
	Card crd3;
	Card crd4;
	std::vector<Card*> CardDeck;
	std::vector<Card*>::iterator CardDeckIterator;
};
