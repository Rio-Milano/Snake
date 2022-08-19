#ifndef TWO_PLAYERSNAKE_H
#define TWO_PLAYERSNAKE_H

#include"Snake.h"

/*

this class represents the seccond player snake that users can enable in the configure scene

*/

class Two_PlayerSnake : public  Snake//implements the base snake class
{
public:
	//passes attribuites to the snake constructor 
	explicit Two_PlayerSnake(const sf::Vector2f& top_left_grid_point_, const sf::Vector2f& bottom_right_grid_point_, const std::string& snake_name_)
		: Snake(top_left_grid_point_, bottom_right_grid_point_, snake_name_) {};
	
	~Two_PlayerSnake() {};

	//gets input for the snake
	void Class_Input_(std::vector< std::shared_ptr<Collectable>>& collectables_) override final;

};

#endif

