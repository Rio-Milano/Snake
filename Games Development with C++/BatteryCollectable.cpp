#include "BatteryCollectable.h"

#include<SFML/Graphics.hpp>

#include"Window.h"
#define Window  Window::Instance_()

#include"TextureManager.h"
#define TextureManager  TextureManager::Instance_()



BatteryCollectable::BatteryCollectable(const sf::Vector2f& pos_) : Collectable(pos_)//pass data to collectable to process
{
	//set type of collectable to battery
	collectable_type_ = E_CollectableType::eBattery;

	//sets texture of collectable to battery
	collectable_icon_.setTexture(TextureManager.Get_Texture_("Battery_Texture"));
}

void BatteryCollectable::Render_()
{
	//if the collectable is alive then draw it to the window
	if (isAlive)
	{
		//set the collectable position
		collectable_icon_.setPosition(pos_);

		//draw the collectable 
		Window.Render_Window_Entity_(collectable_icon_);
	}
}

void BatteryCollectable::Update_()
{
	//update the switch texture timer
	timer_toggle_for_texture_type_--;

	//if switch texture timer is over
	if (timer_toggle_for_texture_type_ == 0)
	{
		//reset the timer count
		timer_toggle_for_texture_type_ = MAX_timer_toggle_for_texture_type_;

		//if the texture of collectable default texture
		if (is_default_texture_)
		{
			//set not default as flag
			is_default_texture_ = false;

			//update the texure
			collectable_icon_.setTexture(TextureManager.Get_Texture_("Battery_Texture_Invert"));
		}
		else//if the default texture is not set
		{
			//set default texture as flag
			is_default_texture_ = true;

			//set the collectable texure to default 
			collectable_icon_.setTexture(TextureManager.Get_Texture_("Battery_Texture"));
		}
	}
}
