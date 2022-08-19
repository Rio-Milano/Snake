#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

	class Button
	{
	public:
		//ctor and dtor
		explicit Button
		(
			const sf::Vector2f& image_screen_pos_, 
			const std::string& button_text_, 
			const sf::Vector2f& button_text_pos_, 
			const unsigned int& button_text_size_, 
			const sf::Color& button_text_color_,
			const sf::Vector2f& size_ = {540, 146}
		);
		~Button();

		/*
		
		utility functions 

		*/

		//draw the button to the window
		void Render();

		//update the button
		void Update();

		//get if the button has been clicked 
		bool Get_Is_Clicked_(const bool& play_sound_ = true);

		//reset button states
		void Reset_Button_();

		//set the text upon the button
		inline void Set_Button_Text_(const std::string& text_) { this->button_screen_text_.setString(text_); };
		
		//set the button text fill color 
		inline void Set_Button_FillColor_(const sf::Color& color) { this->button_screen_text_.setFillColor(color); }



	private:
		/*

		utility functions

		*/

		//is the mouse hovering over the button
		bool mouse_over_button_(const sf::Vector2f&) const;

		//status for button being previously pressed
		bool button_is_locked_ = false;

		//text for the button
		sf::Text button_screen_text_;

		//the button shape
		sf::RectangleShape button_rect_;

	};

#endif