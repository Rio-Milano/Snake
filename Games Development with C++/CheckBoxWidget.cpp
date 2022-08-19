#include "CheckBoxWidget.h"

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
 CheckBoxWidget::CheckBoxWidget
(
	const sf::Vector2f& position_,
	const sf::Vector2f& size_
)
{
	 //set the outer layer of the checkbox attribiutes
	check_box_rect_.setPosition(position_);
	check_box_rect_.setFillColor(sf::Color::White);
	check_box_rect_.setSize(size_);

	//set the inner layers of the checkbox attributes
	inner_box_rect.setPosition(position_.x + 5, position_.y + 5);
	inner_box_rect.setSize({ size_.x - 10, size_.y - 10 });

}

 CheckBoxWidget::~CheckBoxWidget()
{
}

/*

utility functions

*/

 void  CheckBoxWidget::Render()
{
	 //draw the checkbox to the window
	Window.Render_Window_Entity_(check_box_rect_);
	Window.Render_Window_Entity_(inner_box_rect);

}

void  CheckBoxWidget::Update()
{
	//if the checkbox is not toggled
	if(On_Off == false)
		//set the inner color of the check box to red
		inner_box_rect.setFillColor(sf::Color::Red);
	//if the checkbox is toggled
	else
		//set the inner color of the checkbox to green
		inner_box_rect.setFillColor(sf::Color::Green);

}



const bool  CheckBoxWidget::Get_Is_Clicked_(const bool& play_sound_)
{
	//if the checkbox is not blocking input
	if (!check_box_locked)
	{
		//if the mouse is hovering over the checkbox
		if (mouse_over_checkbox_(sf::Vector2f(float(MousePos.x), float(MousePos.y))))
		{
			//if the window polled a left mouse button press
			if (Window.Get_Event_().type == sf::Event::MouseButtonPressed && Window.Get_Event_().mouseButton.button == sf::Mouse::Left)
			{
				//if the sound is being asked to play then play the sound for click
				play_sound_ ?  SoundManager::Instance_().Play_Sound_("ButtonClick") : void();

				//toggle the toggle variable 
				On_Off = !On_Off;

				//block input for the checkbox
				check_box_locked = true;

				//return true for clicked
				return true;
			}
		}
		//return false for not clicked
		return false;
	}
	else//if the checkbox is blocking input
	{
		//if the window polled a left mouse button released event
		if (Window.Get_Event_().type == sf::Event::MouseButtonReleased &&
			Window.Get_Event_().mouseButton.button == sf::Mouse::Left)
		{
			//disable input blocking for checkbox
			check_box_locked = false;
		}

	}
	//return false for not clicked
	return false;
}

void  CheckBoxWidget::Reset_CheckBox_()
{
	//reset all checkbox attributes 
	On_Off = false;
	check_box_locked = false;
	inner_box_rect.setFillColor(sf::Color::White);
}



//private utility function
const bool  CheckBoxWidget::mouse_over_checkbox_(const sf::Vector2f& mouse_pos_)
{
	//if the mouse is in range of the x axis of the checkbox
	if (mouse_pos_.x > check_box_rect_.getPosition().x &&
		mouse_pos_.x < check_box_rect_.getPosition().x + check_box_rect_.getSize().x)
	{
		//if the mouse is in rangd of the y axis of the checkbox
		if (mouse_pos_.y > check_box_rect_.getPosition().y &&
			mouse_pos_.y < check_box_rect_.getPosition().y + check_box_rect_.getSize().y)
			//return true for mouse is hovering on checkbox
			return true;
	}
	//return false for mouse is not hovering over checkbox
	return false;
}
