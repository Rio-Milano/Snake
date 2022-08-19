#include "WhiteScene.h"

#include"SceneManager.h"
#define SceneManager  SceneManager::Instance_()

//init list to set up white effect
WhiteScene::WhiteScene() :white_shape_overlay(static_cast<sf::Vector2f>(Window.Get_Screen_Size_()))
{
	//set attributes of white effect
	sf::Color window_color_ = sf::Color(0, 0, 0, current_screen_opacity_);
	white_shape_overlay.setFillColor(window_color_);
};

void WhiteScene::Update_()
{
	//if the opacity velocity is negative and applying it to the opacity would result in underflow then the effect is finished
	if (color_change_velocity_ < 0 && current_screen_opacity_ + color_change_velocity_ <= 0)
	{
		//remove the scene from the stack
		SceneManager.Pop_Scene_(); 

		//exit the update 
		return;
	}
	//if the color change velocity is positive and applying it to opacity results in overflow then
	if (color_change_velocity_ > 0 && current_screen_opacity_ + color_change_velocity_ >= 100)
	{
		//remove the scene from the stack
		SceneManager.Pop_Scene_(); 

		//exit the update
		return;
	}

	//apply the opacity velocity to the opacity
	current_screen_opacity_ += color_change_velocity_;

	//get a new color from the new opacity
	sf::Color white_shape_overlay_color = sf::Color(0, 0, 0, current_screen_opacity_);
	
	//set the color of the white effect
	white_shape_overlay.setFillColor(white_shape_overlay_color);


}

//load the effect
inline void WhiteScene::Init_()
{
};

//unload the effect
void WhiteScene::De_Init_()
{
	//reset opacity
	current_screen_opacity_ = 255u;

	//reset opacity velocity
	color_change_velocity_ = -4;

	//update the color of the white effcect
	sf::Color white_shape_overlay_color = sf::Color(0, 0, 0, current_screen_opacity_);
	
	//set the color of the white effect
	white_shape_overlay.setFillColor(white_shape_overlay_color);
};