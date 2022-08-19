#include "Two_PlayerSnake.h"

#include"Window.h"
#define Window  Window::Instance_()

#include"Direction.h"

void Two_PlayerSnake::Class_Input_(std::vector< std::shared_ptr<Collectable>>& collectables_)
{
	//decode the input polled from the window
	switch (Window.Get_Event_().key.code)
	{
		//W makes the snake go UP
		case sf::Keyboard::W:
			Change_Direction_( Direction::eUp);
			break;
		//D makes the snake go right
		case sf::Keyboard::D:
			Change_Direction_( Direction::eRight);
			break;
		//S makes the snake go down
		case sf::Keyboard::S:
			Change_Direction_( Direction::eDown);
			break;
		//A makes the snake go left
		case sf::Keyboard::A:
			Change_Direction_( Direction::eLeft);
			break;
	}
}
