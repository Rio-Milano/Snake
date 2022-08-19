#include "SlideBar.h"

#include"Window.h"
#define Window  Window::Instance_()

SlideBar::SlideBar(const sf::Vector2f& pos_, const sf::Vector2f& size_, const sf::Color& bg_color_)
	: bg_rectangle_(size_), fg_rectangle_((size_.y - 40)/2),//init list to setup slidebar components 
	progress_bar_text_("0", pos_, 0, 0, 20, sf::Color::White)
{
	//set attributes for the bg shape
	bg_rectangle_.setPosition(pos_);
	bg_rectangle_.setFillColor(bg_color_);

	//set attributes for the notch
	fg_rectangle_.setPosition({pos_.x + 2, pos_.y + 20});
	fg_rectangle_.setFillColor(sf::Color::Black);



};

void SlideBar::Render_()
{
	//render components to the window
	Window.Render_Window_Entity_(bg_rectangle_);
	Window.Render_Window_Entity_(fg_rectangle_);
	progress_bar_text_.Render_();
}


void SlideBar::Update_()
{
	//get the mouse position
	sf::Vector2i mouse_pos_ = sf::Mouse::getPosition();

	//if the mouse left button is pressed
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{

		//if the mouse is over the fg component 
		if (mouse_pos_.x > fg_rectangle_.getPosition().x && mouse_pos_.y > fg_rectangle_.getPosition().y &&
			mouse_pos_.x < fg_rectangle_.getPosition().x + fg_rectangle_.getRadius()*2 &&
			mouse_pos_.y < fg_rectangle_.getPosition().y + fg_rectangle_.getRadius()*2)
		{
			//set the flag for mouse locked into fg component 
			is_locked_onto = true;
			
			//maintain distance set to the offset from the mouse pos and the fg component 
			maintained_distance = mouse_pos_.x - fg_rectangle_.getPosition().x;
		}
	}
	else
		//if mouse not pressed then not locked onto it
		is_locked_onto = false;

	//if locked onto the fg component 
	if (is_locked_onto)
	{
		//calculate the new x position using the maintained distance 
		float newX = mouse_pos_.x - maintained_distance;

		//if the newX is out of range of the bg component then exit
		if (newX <= bg_rectangle_.getPosition().x)
			return;
		//if the end newX is out of range from the bg component then exit
		if (newX + fg_rectangle_.getRadius()*2 >= bg_rectangle_.getPosition().x + bg_rectangle_.getSize().x)
			return;

		//update fg position
		fg_rectangle_.setPosition(mouse_pos_.x - maintained_distance, fg_rectangle_.getPosition().y);	

	}
		//update text position
		progress_bar_text_.Set_Position_({ fg_rectangle_.getPosition().x + 20, fg_rectangle_.getPosition().y - 25 });
	
		//update text
		progress_bar_text_.Set_Text_(std::to_string(static_cast<int>(Get_Percentage_() * 100)) + "%");


}
const float SlideBar::Get_Percentage_()
{
	//find the horizontal distance from the fg component and the bg component
	float fg_pos = fg_rectangle_.getPosition().x - bg_rectangle_.getPosition().x;

	//get the total values we can get on the bg component
	float total_fg_pos_ = bg_rectangle_.getSize().x - (2 * fg_rectangle_.getRadius()) - 5;

	//find a percentage from where abouts the fb component is 
	float x = fg_pos / total_fg_pos_;

	//convert to float to abstract the long number to just get 4
	std::string new_string = std::to_string(x).substr(0, 4);

	//convert value back to float and return it
	return std::stof(new_string);
}
;