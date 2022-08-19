#include "Button.h"

#define MousePos sf::Mouse::getPosition()

#include "Window.h"
#define Window Window::Instance_()

#include "TextureManager.h"
#define TextureManager  TextureManager::Instance_()

#include"FontManager.h"
#define FontManager  FontManager::Instance_()

#include "SoundManager.h"
#define Sound  SoundManager::Instance_()

//ctor and detor
 Button::Button
(
	const sf::Vector2f& image_screen_pos_,
	const std::string& button_text_,
	const sf::Vector2f& button_text_pos_,
	const unsigned int& button_text_size_,
	const sf::Color& button_text_color_,
	const sf::Vector2f& size_
) ://padd params to button screen text
	button_screen_text_(button_text_, FontManager.Get_Font_("ButtonText"), button_text_size_)
{
	 //set button rectangle attributes 
	button_rect_.setFillColor(sf::Color(255, 255, 255, 80));
	button_rect_.setSize(size_);
	button_rect_.setPosition(image_screen_pos_);
	
	//set button text attributes
	button_screen_text_.setPosition(button_text_pos_);
	button_screen_text_.setFillColor(button_text_color_);
	button_screen_text_.setOutlineColor(sf::Color::Black);
	button_screen_text_.setOutlineThickness(3);
}

 Button::~Button()
{
}

/*

utility functions

*/

void  Button::Render()
{
	//draw the button rectangle to the screen
	Window.Render_Window_Entity_(button_rect_);
	//draw the button text to the screen
	Window.Render_Window_Entity_(button_screen_text_);
}

void  Button::Update()
{
	//if the mouse is over the button
	if (mouse_over_button_(sf::Vector2f(float(MousePos.x), float(MousePos.y))))
		button_rect_.setFillColor(sf::Color(0, 0, 0, 80));//set the button rectangle fill color to light black

	else//if the mouse is not over the button
		button_rect_.setFillColor(sf::Color(255, 255, 255, 80));//set the button fill color to light white
}



bool  Button::Get_Is_Clicked_(const bool& play_sound_)
{
	//if the button is not blocking input
	if (!button_is_locked_)
	{
		//if the mouse is over the button
		if (mouse_over_button_(sf::Vector2f(float(MousePos.x), float(MousePos.y))))
		{
			//if the window polled a left click event
			if (Window.Get_Event_().type == sf::Event::MouseButtonPressed && Window.Get_Event_().mouseButton.button == sf::Mouse::Left)
			{
				//if playing sound is true then play sound for click
				play_sound_ ?  SoundManager::Instance_().Play_Sound_("ButtonClick") : void();

				//prevent input events
				button_is_locked_ = true;

				//return true for clicked
				return true;
			}
		}
		return false;
	}
	//if input events are being blocked 
	else
	{
		//if the window polled a mouse released for left button
			if (Window.Get_Event_().type == sf::Event::MouseButtonReleased && 
				Window.Get_Event_().mouseButton.button == sf::Mouse::Left)
				button_is_locked_ = false;//reinstate input events

	}
	//return false for not clicked
	return false;
}

void  Button::Reset_Button_()
{
	//set blocking input events to false
	button_is_locked_ = false;

	//reset button rectagle fill color to unpressed 
	button_screen_text_.setFillColor(sf::Color::White);
}



//private utility function
bool  Button::mouse_over_button_(const sf::Vector2f& mouse_pos_) const
{
	//if the mouse is in range of x button axis
	if (mouse_pos_.x > button_rect_.getPosition().x && 
		mouse_pos_.x < button_rect_.getPosition().x + button_rect_.getSize().x)
	{
		//if button is in range of y button axis
		if (mouse_pos_.y > button_rect_.getPosition().y &&
			mouse_pos_.y < button_rect_.getPosition().y + button_rect_.getSize().y)
			
			//return true for mouse cursor is in range
			return true;
	}
	//return false for mouse cursor not in rangee
	return false;
}
