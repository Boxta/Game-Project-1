#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "Card.h"
#include <random>

class BoardState;

class Player
{
public:
	Player(Game& ref);
	~Player();
	void Initiate(float x, float y, 
		std::string name);
	void Update(const float dt);
	void Draw();
	Card& GetTopCard();
	Card& GetCard(const sf::FloatRect id);
	int GetDeckCount() { return CardDeck.size(); }
	void CycleDeck();
	void Turn(BoardState& brd, float xX, float yY);
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
	std::vector<Card>::iterator DeckIterator;
	int mCardDeckIterator = 0;
	bool mIterateDirection = true;
	bool CheckSafeBoardPosition(sf::Vector2i vec, int boardwidth, int boardheight);
	std::random_device rd;  
	std::mt19937 rng;
};

