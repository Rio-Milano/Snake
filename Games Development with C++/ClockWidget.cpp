#include "ClockWidget.h"

ClockWidget::ClockWidget(const sf::Vector2f& bg_shape_pos_, const sf::Vector2f& text_pos_, const double& total_time_, const float& bg_shape_raduis, const sf::Color& bg_bg_color, const sf::Color& bg_fg_color, const float& bg_fg_thic, const sf::Color& text_color_)
	:
	total_time_(total_time_),//set variables
	copy_total_time_(total_time_),
	bg_shape(bg_shape_raduis),
	text_widget_(std::to_string(total_time_).substr(0, 5), text_pos_, 0, 0, 30, text_color_)
{
	//set attributes of the clock shape
	bg_shape.setFillColor(bg_bg_color);
	bg_shape.setOutlineThickness(bg_fg_thic);
	bg_shape.setOutlineColor(bg_fg_color);
	bg_shape.setPosition(bg_shape_pos_);
}
void ClockWidget::Update_Clock_()
{
	//if the clock is counting down
	if (is_timer_started_)
	{
		//if the clock still has time remaining
		if (total_time_ > 0)
		{
			//subtract the time that will pass in a frame
			total_time_ -= 0.0166666667;

			//if time remaining has underflowed 
			if (total_time_ < 0)
			{
				total_time_ = 0;//set time remaining to 0
				timer_over_ = true;
			}

			//update the text on the clock to show time remaining 
			text_widget_.Set_Text_((std::to_string(total_time_).substr(0, 5)));


		}

	}
}

void ClockWidget::Render_()
{
	//render the clock shape
	Window.Render_Window_Entity_(bg_shape);

	//get the percentage of the clock completing the timer
	float percentage_of_color_ = (float)total_time_ / (float)copy_total_time_;

	//calculate the green color in the clock text
	unsigned int green_ = static_cast<unsigned int> (MAX_COLOR_VALUE * percentage_of_color_);

	//calculate the red color in the clock text
	unsigned int red_ = static_cast<unsigned int>(MAX_COLOR_VALUE - green_);

	//create a new color
	sf::Color new_color_ = sf::Color(red_, green_, MIN_COLOR_VALUE);

	//set the text of the clock text to the new adjusted color
	text_widget_.Set_Text_Color_(new_color_);

	//render the text of the clock
	text_widget_.Render_();

}

void ClockWidget::ResetClock()
{
	//set the time to count down from to the backup time
	total_time_ = copy_total_time_;

	//stop the timer
	is_timer_started_ = false;

	//make the timer start from beguinning 
	timer_over_ = false;

	//set the text of the clock to the new time to count down from
	text_widget_.Set_Text_(std::to_string(total_time_).substr(0, 5));
}