#ifndef CLOCKWIDGET_H
#define CLOCKWIDGET_H

#include"Window.h"
#define Window Window::Instance_()

#include"Text.h"
#include<string>

//the largest color and the minimum color on the RGB color range
#define MAX_COLOR_VALUE  255
#define MIN_COLOR_VALUE 0

#include<SFML/Graphics.hpp>
#include<iostream>

class ClockWidget
{
public:
	explicit ClockWidget(
		const sf::Vector2f& bg_shape_pos_,
		const sf::Vector2f& text_pos_,
		const double& total_time_,
		const float& bg_shape_raduis,
		const sf::Color& bg_bg_color, 
		const sf::Color& bg_fg_color, 
		const float& bg_fg_thic, 
		const sf::Color& text_color_);

	//get the remaining time on the clock
	inline const double& Get_Time_Left_() const{ return this->total_time_; }

	//turn on the timer
	inline void Toggle_Clock_()
	{
		this->is_timer_started_ = true;
	}

	//get is the clock timer finished
	inline const bool& Get_Is_Time_Over_()const
	{
		return this->timer_over_;
	}
	
	//update the timer
	void Update_Clock_();

	//get has the timer started
	inline const bool& Get_Is_Clock_Started_()const
	{
		return this->is_timer_started_;
	}

	//draw the clock to the window
	void Render_();

	//reset all attributes of the clock
	void ResetClock();

private:
	//the time to cout down from
	double total_time_;

	//a copy of the initial time to count down from
	double copy_total_time_;

	//a flag to show if the timer is counting down or now
	bool is_timer_started_ = false;

	//a flag to show if timer is over
	bool timer_over_ = false;

	//the shape for the back of the clock
	sf::CircleShape bg_shape;

	//the text for the clock
	 Text text_widget_;

};

#endif

