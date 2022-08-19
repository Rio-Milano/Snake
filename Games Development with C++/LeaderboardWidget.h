#ifndef LEADERBOARDWIDGET_H
#define LEADERBOARDWIDGET_H

#include <SFML/Graphics.hpp>
#include<vector>
#include"Snake.h"
#include"Text.h"

/*

this class represents the widget on the top left of the screen in the game scene that shows the top two snakes

*/

class LeaderboardWidget
{
public:

	//ctors and dtors
	explicit LeaderboardWidget(const sf::Vector2f& position_);
	~LeaderboardWidget() = default;

	//draw the widget to the window
	void Render_();

	//update the widget
	void Update_(std::vector< std::shared_ptr<Snake>> snakes_);

	//reset the widget attributes
	void Reset_();


private:
	//background of widget
	sf::RectangleShape white_shape_;

	//snake 1 and 2 image
	sf::Sprite snake_1_sprite;
	sf::Sprite snake_2_sprite;

	//snake 1 and 2 name
	Text snake_1_text_;
	Text snake_2_text_;

	//snake 1 and 2 score shape
	sf::RectangleShape snake_1_progress_bar_;
	sf::RectangleShape snake_2_progress_bar_;

	//snake 1 and 2 score text
	Text snake_1_progress_bar_value_text_;
	Text snake_2_progress_bar_value_text_;

	//shape in winning position
	std::shared_ptr<Snake> snake_in_first_place_{nullptr};
	
	//shape in seccond to winning position
	std::shared_ptr<Snake> snake_in_seccond_place_ = { nullptr };




};

#endif