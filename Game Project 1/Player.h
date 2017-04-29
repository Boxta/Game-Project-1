#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "Card.h"
#include <algorithm>

class Player
{
public:
	Player(Game& ref);
	~Player();
	void Initiate(float x, float y, 
		std::string name,
		float xn, float yn);
	void Update(const float dt);
	void Draw();
	Card& GetTopCard();
	int GetDeckCount() { return CardDeck.size(); }
	void CycleDeck();
	void KillTopCard();
private:
	sf::Vector2f mHandPositionA;
	sf::Vector2f mHandPositionB;
	sf::Vector2f mHandPositionC;
	Game& mGameReference;
	sf::Text mName;
	sf::Sprite mSprite;
	Card crd1;
	Card crd2;
	Card crd3;
	Card crd4;
	std::vector<Card*> CardDeck;
	std::vector<Card*>::iterator DeckIterator;
	int mCardDeckIterator = 0;
};

