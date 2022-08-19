#include "Utils.h"



float  lerp(const float& point_a, const float& point_b, const float& units_)
{
	//take point A
	//take thee coefficient 0 <= units <= 1
	//multiply the coefficient by the vector AB for a 1D

	return point_a + units_ * (point_b - point_a);
}

const sf::Vector2f Get_Grid_Point_(sf::Vector2f orig_, sf::Vector2f point_scale, sf::Vector2f points_unit_)
{
	sf::Vector2f new_point_;
	new_point_.x = orig_.x + point_scale.x * points_unit_.x;
	new_point_.y = orig_.y + point_scale.y * points_unit_.y;

	return new_point_;
}

void Set_Direction_To_Random(Direction& direction_)
{
	switch (rand() % 4)
	{
	case 0:
		direction_ = Direction::eLeft;
		break;
	case 1:
		direction_ = Direction::eRight;
		break;
	case 2:
		direction_ = Direction::eUp;
		break;
	case 3:
		direction_ = Direction::eDown;
		break;
	}

}