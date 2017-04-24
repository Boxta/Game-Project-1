#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "Card.h"


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
	Card& GetClickedCard(sf::FloatRect& ref);
private:
	Game& mGameReference;
	sf::Text mName;
	sf::Sprite mSprite;
	Card crd1;
	Card crd2;
	Card crd3;
	Card crd4;
};

