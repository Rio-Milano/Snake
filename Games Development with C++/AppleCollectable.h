
#ifndef APPLECOLLECTABLE_H
#define APPLECOLLECTABLE_H


#include "Collectable.h"
#include "SFML/Graphics.hpp"

/*

represents the apples that snakes can eat in the game

*/


class AppleCollectable : public  Collectable//implements base class collectable 
{
public:
	//ctors and dtor
	explicit AppleCollectable(const sf::Vector2f& pos_);

	~AppleCollectable() = default;

	//draw the apple 
	void Render_() override final;

	//update the apple
	void Update_() override final;



};

#endif
