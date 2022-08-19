#include<SFML/Graphics.hpp>
#include "Direction.h"


//function to find a point within 2 points
float lerp(const float& point_a, const float& point_b, const float& units_);

//used for getting random points on the game grid
const sf::Vector2f Get_Grid_Point_(sf::Vector2f orig_ = { 440.f, 40.f }, sf::Vector2f point_scale = { float(rand() % 25),+float(rand() % 25) }, sf::Vector2f points_unit_ = { 40.f, 40.f });

//used for random direction setting
void Set_Direction_To_Random(Direction& direction_);