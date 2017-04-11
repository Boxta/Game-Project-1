#include "TestState.h"

TestState::TestState() :
	shape(300.0f)
{
	shape.setFillColor(sf::Color::Blue);
}


TestState::~TestState()
{
}

void TestState::HandleInput()
{

}

void TestState::Update(float dt)
{

}

void TestState::Draw(float dt, sf::RenderWindow& wnd)
{

	//Clear the window before drawing
	wnd.clear();
	//Draw the shape to the cleared window
	wnd.draw(shape);
}
