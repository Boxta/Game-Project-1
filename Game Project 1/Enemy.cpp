#include "Enemy.h"
#include "Game.h"
#include "BoardState.h"

Enemy::Enemy(Game& ref)
	:
	mGameReference(ref),
	crd1(ref),
	crd2(ref),
	crd3(ref),
	crd4(ref)
{
}


Enemy::~Enemy()
{
}

Card& Enemy::GetTopCard()
{
	return *CardDeck.back();
}

Card& Enemy::UseTopCard()
{
	Card& tmp = *CardDeck.back();
	tmp.ResetColor();
	CardDeck.pop_back();
	return tmp;
}

void Enemy::CycleDeck()
{

	CardDeckIterator = CardDeck.begin();
	Card* tmp = CardDeck.back();
	CardDeck.pop_back();
	CardDeck.insert(CardDeckIterator, tmp);
}

void Enemy::Turn(BoardState& brd)
{
	/*Enemy Is First Turn*/
	if (brd.GetDeck().size() <= 0)
	{
		//Ad Code Here
		return;
	}

	//Check Cards On Board.
	for(auto& u : brd.GetDeck())
	{
		const int nTop = u->mValue_Top;
		const int nDown = u->mValue_Down;
		const int nLeft = u->mValue_Left;
		const int nRight = u->mValue_Right;

		bool opnTop = false;
		bool opnDown = false;
		bool opnLeft = false;
		bool opnRight = false;

		/*Create Rectangles Around Card*/
		const sf::FloatRect recTop(u->GetRectangle().left, u->GetRectangle().top - 350.0f, 250.0f, 300.0f);
		const sf::FloatRect recDown(u->GetRectangle().left, u->GetRectangle().top + 350.0f, 250.0f, 300.0f);
		const sf::FloatRect recLeft(u->GetRectangle().left - 300.0f, u->GetRectangle().top, 250.0f, 300.0f);
		const sf::FloatRect recRight(u->GetRectangle().left + 300.0f, u->GetRectangle().top, 250.0f, 300.0f);

		/*Identify Board Spaces That Meet Criteria*/
		for (auto& y : brd.GetSlots())
		{
			if (y.GetCardRectangle() == recTop &&
				y.GetIsUsed() == false)
			{
				int i = 0;
				opnTop = true;
			}
			if (y.GetCardRectangle() == recDown &&
				!y.GetIsUsed())
			{
				opnTop = true;
			}
			if (y.GetCardRectangle() == recLeft &&
				!y.GetIsUsed())
			{
				opnTop = true;
			}
			if (y.GetCardRectangle() == recRight &&
				!y.GetIsUsed())
			{
				opnTop = true;
			}
		}

		/*Check and Place Cards*/
		/*RETURN IF WIN FOUND*/
		for (auto& k : CardDeck)
		{
			if (opnTop)
			{
				if (k->mValue_Down > u->mValue_Top)
				{
					for (auto& y : brd.GetSlots())
					{
						if (y.GetCardRectangle() == recTop)
						{
							y.ToogleUse();
						}
					}
					//while (CardDeck.back()->GetRectangle() != k->GetRectangle())
					//{
					//	CycleDeck();
					//}
					k->SetPosition(recTop.left, recTop.top);
					brd.GetDeck().push_back(k);
					//CardDeck.pop_back();
					brd.ToogleTurn();
					return;
				}
				else
				{
					//Lose
				}
			}
			if (opnDown)
			{
				if (k->mValue_Top > u->mValue_Down)
				{
					for (auto& y : brd.GetSlots())
					{
						for (auto& y : brd.GetSlots())
						{
							if (y.GetCardRectangle() == recDown)
							{
								y.ToogleUse();
							}
						}
						//while (CardDeck.back()->GetRectangle() != k->GetRectangle())
						//{
						//	CycleDeck();
						//}
						k->SetPosition(recDown.left, recDown.top);
						brd.GetDeck().push_back(k);
						//CardDeck.pop_back();
						brd.ToogleTurn();
						return;
					}
				}
				else
				{
					//Lose
				}
			}
			if (opnLeft)
			{
				if (k->mValue_Right > u->mValue_Left)
				{
					for (auto& y : brd.GetSlots())
					{
						for (auto& y : brd.GetSlots())
						{
							if (y.GetCardRectangle() == recLeft)
							{
								y.ToogleUse();
							}
						}
						//while (CardDeck.back()->GetRectangle() != k->GetRectangle())
						//{
						//	CycleDeck();
						//}
						k->SetPosition(recLeft.left, recLeft.top);
						brd.GetDeck().push_back(k);
						//CardDeck.pop_back();
						brd.ToogleTurn();
						return;
					}
				}
				else
				{
					//Lose
				}
			}
			if (opnRight)
			{
				if (k->mValue_Left > u->mValue_Right)
				{
					for (auto& y : brd.GetSlots())
					{
						for (auto& y : brd.GetSlots())
						{
							if (y.GetCardRectangle() == recRight)
							{
								y.ToogleUse();
							}
						}
						//while (CardDeck.back()->GetRectangle() != k->GetRectangle())
						//{
						//	CycleDeck();
						//}
						k->SetPosition(recRight.left, recRight.top);
						brd.GetDeck().push_back(k);
						//CardDeck.pop_back();
						brd.ToogleTurn();
						return;
					}
				}
				else
				{
					//Lose
				}
			}
		}

		/*No Win Found*/
		brd.ToogleTurn();
	}


}

void Enemy::Initiate(float x, float y,
	std::string name,
	float xn, float yn)
{
	mSprite.setTexture(mGameReference.GetCommonStore().GetTextureRef("EnemyPicture"));
	mSprite.setPosition(x, y);
	mName.setFont(mGameReference.GetCommonStore().GetFontRef("System"));
	mName.setString(name);
	mName.setPosition(xn, yn);
	mName.setFillColor(sf::Color::Black);
	mName.setCharacterSize(18);

	crd1.Initiate(1620.0f, 50.0f, "Boss A");
	crd2.Initiate(1570.0f, 100.0f, "Boss B");
	crd3.Initiate(1520.0f, 150.0f, "Boss C");
	crd4.Initiate(1470.0f, 200.0f, "Boss D");
	
	CardDeck.push_back(&crd1);
	CardDeck.push_back(&crd2);
	CardDeck.push_back(&crd3);
	CardDeck.push_back(&crd4);
}

void Enemy::Update(const float dt)
{
	for (auto& c : CardDeck)
	{
		c->Update(dt);
	}
}

void Enemy::Draw()
{
	mGameReference.GetWindow().draw(mSprite);
	mGameReference.GetWindow().draw(mName);
	for (int p = 0; p < CardDeck.size(); p++)
	{
		CardDeck[p]->SetPosition(1670 - ((p + 1) * 50), ((p + 1) * 50));
		CardDeck[p]->Draw();
	}
}
