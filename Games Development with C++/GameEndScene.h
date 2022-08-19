#ifndef GAMEENDSCENE_H
#define GAMEENDSCENE_H

#include<SFML/Graphics.hpp>


#include "Scene.h"
#include "Button.h"
#include"Snake.h"
#include"Text.h"
#include<vector>

/*
this scene is a child of scene and is loaded when the game over flag in the game scene is set to true
*/

class GameEndScreen : public  Scene//inherits and implements scene
{
public:
	//ctors and dtors
	GameEndScreen();
	~GameEndScreen() = default;

	//draw the widgets to the window
	void Render_() override final;

	//update the widgets
	void Update_() override final;

	//load the scene
	void Init_() override final {};

	//unload the scene
	void De_Init_() override final;

	//a vector which is an exact coppy of the snakes vector in the game scene that overwrites this vector when the game ends 
	static std::vector< std::shared_ptr<Snake>> snakes_;

private:
	//button to go to the menu
	Button main_menu_button_;

	//button to close the program
	Button exit_button_;
	
	//distorted image to go over the game scene
	sf::Sprite game_over_overlay_;

	//podium image for snakes to be placed upon
	sf::Sprite podium_texture_;

	//snake in first place set
	sf::Sprite snake_in_first_place_spr;
	Text snake_in_first_place_text_;

	//snake in seccond place set
	sf::Sprite snake_in_seccond_place_spr;
	Text snake_in_seccond_place_text_;
		
	//snake in third place set
	sf::Sprite snake_in_third_place_spr;
	Text snake_in_third_place_text_;
	

};

#endif