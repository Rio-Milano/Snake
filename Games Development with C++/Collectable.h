#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include<SFML/Graphics.hpp>
#include "E_CollectableType.h"

/*

this is a base class for collectable items in the game. Child classes will extend and implement this class

*/

class Collectable
{
public:

	//ctors and dtors
	explicit Collectable(const sf::Vector2f& pos_) :pos_(pos_) {
		food_value_ = 1 + rand() % 2;//set the value of the food upon init
	};

	~Collectable() = default;

	//pure virtual

	//draw the collectable onto the window
	virtual void Render_() = 0;

	//update the collectable
	virtual void Update_() = 0;

	//gets the position of the collectable 
	inline const sf::Vector2f& Get_Pos_() const { return this->pos_; };
	
	//sets the position of the collectable
	inline void Set_Pos_(const sf::Vector2f& pos_) { this->pos_ = pos_; this->food_value_ = 1 + rand() % 2; }

	//get is the collectable alive
	inline const bool& Get_Is_Alive_() const { return this->isAlive; };
	
	//set is a collectable is alive
	inline void Set_Is_Alive(const bool& bool_) { this->isAlive = bool_; };

	//get the delay time until a collectable can spawn
	inline const int& Get_Time_Till_Spawn_() const { return this->time_till_spawn_; };
	
	//set the delay time until a collectable can spawn
	inline void Set_Time_Till_Spawn_(int time_ = rand() % 241) { this->time_till_spawn_ = time_; };

	//gets the food value of the collectable
	inline const int& Get_Food_Value_() const { return this->food_value_; };

	//gets the type of the collectable 
	inline const E_CollectableType& Get_Collectable_Type_() const { return this->collectable_type_; };

protected:
	//the sprite for the collectable
	sf::Sprite collectable_icon_;

	//used as a timer to switch between variations of the collectable 
	int timer_toggle_for_texture_type_{ 60 };
	
	//the total delay time
	const int MAX_timer_toggle_for_texture_type_{ 60 };

	//a flag to depict the type of collectable texture 
	bool is_default_texture_{ true };

	//position of the collectable 
	sf::Vector2f pos_{};

	//flag for if the collectable is alive
	bool isAlive{ true };

	//the food value of the collectable
	int food_value_{ 0 };

	//the delay timer to prevent collectable from spawning 
	int time_till_spawn_{ rand() % 241 };

	//the type of the collectable 
	E_CollectableType collectable_type_{E_CollectableType::eNone};


	

};

#endif