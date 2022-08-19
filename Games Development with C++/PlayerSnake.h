#ifndef PLAYERSNAKE_H
#define PLAYERSNAKE_H

#include "Snake.h"

/*
this class is a child class of snake and represents the player snake
*/

class PlayerSnake : public Snake//inherits and implements snake
{
public:
	//ctors and dtors
	PlayerSnake(const sf::Vector2f& top_left_grid_point_, const sf::Vector2f& bottom_right_grid_point_, const std::string& snake_name_)
		: Snake(top_left_grid_point_, bottom_right_grid_point_, snake_name_) {}//init list to pass params to Snake ctor
		
	~PlayerSnake() = default;
		
	//get the input for the player snake
	void Class_Input_(std::vector< std::shared_ptr<Collectable>>& collectables_) override final;
};

#endif