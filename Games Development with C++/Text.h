#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <SFML/Graphics.hpp>

/*

This class functionally acts the same as sf::Text but gives more control + features

*/

class Text
{
public:
	explicit Text(std::string text_, sf::Vector2f pos_, int transparancy_scale_ = 3, float size_scale_ = 0.009, const unsigned int& size_ = 30u, const sf::Color& color_ = sf::Color::Yellow);

	~Text();

	//draw the text to the window
	void Render_();

	//update the text FX
	void Update_();

	//get the string of the text
	inline const std::string& Get_Text_() const { return this->text_.getString(); }

	//set the string of the text
	inline void Set_Text_(const std::string& new_text_) { this->text_.setString(new_text_); }

	//set the location of where the text is rendered 
	inline void Set_Position_(const sf::Vector2f& pos_) { this->text_.setPosition(pos_); };

	//set the color of the text
	inline void Set_Text_Color_(const sf::Color& new_color) { this->text_.setFillColor(new_color); }

	//get the color of the text
	inline const sf::Color& Get_Text_Color_() const{ return this->text_.getFillColor(); }

	//get the position of where the text is on the window
	inline const sf::Vector2f& getPosition() const { return this->text_.getPosition(); }


private:

	//the text that is displayed on window
	sf::Text text_;
		
	//default transparancy of text
	unsigned int transparancy_ = 255;

	//change of transparancy rate
	int transparancy_scale_;

	//change of scale rate 
	float size_scale_;
};
#endif