#ifndef BATTERYCOLLECTABLE_H
#define BATTERYCOLLECTABLE_H

/*

this class implements collectable and represents the battery snakes can collect

*/

#include"Collectable.h"

class BatteryCollectable : public  Collectable//inherits from collectable 
{
public:
	//ctors and dtors
	explicit BatteryCollectable(const sf::Vector2f& pos_);

	~BatteryCollectable() = default;

	//implementing collectable

	//draw elemnts to window
	void Render_() override final;

	//update elements 
	void Update_() override final;
};

#endif