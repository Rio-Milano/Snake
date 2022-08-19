#ifndef AISNAKE_H
#define AISNAKE_H


#include "Snake.h"
#include"Collectable.h"

/*
this class represents the AI snake which is a child class of snake
*/

class AISnake : public  Snake//inherits and implements snake
{
public:
	//constructors and deconstructors
	explicit AISnake
	(//init list to set attributes
		const sf::Vector2f& top_left_grid_point_,
		const sf::Vector2f& bottom_right_grid_point_,
		const std::string& snake_name_
	) : Snake(top_left_grid_point_, bottom_right_grid_point_, snake_name_) {};

	~AISnake() = default;

	//get attributes
	void Class_Input_(std::vector< std::shared_ptr<Collectable>>& collectables_) override final;

private:
	//is the snake going to a collectable
	bool locked_onto_a_collectable = false;

	//start and end positions for path finding
	int	startX{}, startY{}, goalX{}, goalY{};

	//the collectable the snake is locked on to
	std::shared_ptr<Collectable> coll = nullptr;
		
};

#endif