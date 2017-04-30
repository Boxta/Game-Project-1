#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "Card.h"

class BoardState;

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
	void Turn(BoardState& brd, float xX, float yY);
private:
	sf::Vector2f mHandPositionA;
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
	bool mIterateDirection = true;
	bool CheckSafeBoardPosition(sf::Vector2i vec, int boardwidth, int boardheight);
	std::random_device rd;     // only used once to initialise (seed) engine
};

