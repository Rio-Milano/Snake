#include "Animation.h"

#include "Window.h"
#define Window  Window::Instance_()

#include "TextureManager.h"
#define TextureManager  TextureManager::Instance_()

//ctors and dtors
 Animation::Animation(const sf::Vector2f& scale_, const sf::Vector2f& pos_, const int& anim_count_) :
	scale_(scale_),//set variables 
	position_(pos_),
	animation_count_(anim_count_)
{
	sprite_.scale(scale_);//set scale of sprite
	sprite_.setPosition(position_);//set position of sprite
}
 Animation::~Animation()
{
}


//utility functions
void  Animation::Render_()
{
	//set the texure of the sprite using the current frame of animation 
	sprite_.setTexture(TextureManager.Get_Texture_From_Animation_("SnakeStartAnim", animation_index_));
	
	//draw the sprite
	Window.Render_Window_Entity_(sprite_);
}

void  Animation::Update_()
{
	//update the animation index
	animation_index_++;
	
	//error check the animation index for overflow
	animation_index_ >= animation_count_ ? animation_index_ = 0 : animation_index_;
}
