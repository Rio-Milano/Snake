#include "PlayerSnake.h"

#include"Window.h"
#define Window Window::Instance_()

//get the input for the player snakee
void  PlayerSnake::Class_Input_(std::vector< std::shared_ptr<Collectable>>& collectables_)
{
	//decode the window polled event
	switch (Window.Get_Event_().key.code)
	{
	//UP arrow makes snake go up
	case sf::Keyboard::Up:
		Change_Direction_(Direction::eUp);
		break;

	//right arrow make snake go right
	case sf::Keyboard::Right:
		Change_Direction_(Direction::eRight);
		break;

	//down arrow make snake go gown
	case sf::Keyboard::Down:
		Change_Direction_(Direction::eDown);
		break;

	//left arrow make snake go left
	case sf::Keyboard::Left:
		Change_Direction_(Direction::eLeft);
		break;

	}
}
