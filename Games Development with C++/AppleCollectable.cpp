#include "AppleCollectable.h"

#include "Window.h"
#define Window  Window::Instance_()

#include "TextureManager.h"
#define TextureManager  TextureManager::Instance_()

AppleCollectable::AppleCollectable(const sf::Vector2f& pos_) : Collectable(pos_)
{
	//set the collectable type to food
	collectable_type_ = E_CollectableType::eFood;

	//set the icon to the apple texture 
	collectable_icon_.setTexture(TextureManager.Get_Texture_("Apple_Texture"));

}

void AppleCollectable::Render_()
{
	//if the apple hasnt been eaten
	if (isAlive)
	{
		//set the base class sprite position for collectable 
		collectable_icon_.setPosition({ pos_.x, pos_.y });
		
		//render apple
		Window.Render_Window_Entity_(collectable_icon_);
	}
}
void AppleCollectable::Update_()
{
	//update time until apple can spawn
	time_till_spawn_ -= 1;

	//update time until apple can switch textures
	timer_toggle_for_texture_type_ -= 1;

	//if texture can toggle
	if (timer_toggle_for_texture_type_ == 0)
	{
		//reset texture toggle timer 
		timer_toggle_for_texture_type_ = MAX_timer_toggle_for_texture_type_;
		
		//if the apple is set to the default texture
		if (is_default_texture_)
		{
			//set it to the adjusted texture 
			is_default_texture_ = false;

			//set the actual textue to the adjusted texture
			collectable_icon_.setTexture(TextureManager.Get_Texture_("Apple_Texture_Invert"));
		}
		else
		{
			//if the apple is set to the adjusted texture 

			//change it to the default texture
			is_default_texture_ = true;

			//update the texture
			collectable_icon_.setTexture(TextureManager.Get_Texture_("Apple_Texture"));
		}
	}
};

