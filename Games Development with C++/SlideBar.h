#ifndef SLIDEBAR_H
#define SLIDEBAR_H

#include<SFML/Graphics.hpp>
#include"Text.h"

/*
this class represents the slide bar found in the configure scene that is used to adjust 
the volume level of different sounds within the game
*/

class SlideBar
{
public:
	//ctors and dtors
	explicit SlideBar(const sf::Vector2f& pos_, const sf::Vector2f& size_, const sf::Color& bg_color_);
	~SlideBar() = default;

	//draw components of the slide bar to the window
	void Render_();

	//update slidebar 
	void Update_();

	//get the value of the slidebar position in terms of 0->1 to 4dp
	const float Get_Percentage_();

private:
	//the bg shape of the slidebar
	sf::RectangleShape bg_rectangle_;

	//the nob used to adjust the slide bar value
	sf::CircleShape fg_rectangle_;

	//value used to ensure the slide bar notch stays held onto the mouse when dragging 
	float maintained_distance{};

	//the percentage shown to the user on the window for the slide bar value
	Text progress_bar_text_;

	//is the mouse locked onto the slidebar notch
	bool is_locked_onto = false;

};

#endif