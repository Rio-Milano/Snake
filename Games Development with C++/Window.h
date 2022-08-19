#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>

/*

This class represents the SFML window

*/

class Window
{
public:

	/*
		Getters
	*/

	//Gets the singleton of the window class
	static Window& Instance_();

	//Gets if the window is open
	inline const bool Get_Is_Window_Open() const
	{
		return window_.isOpen();
	};

	//gets the window screen size
	inline const sf::Vector2u Get_Screen_Size_() const
	{
		return window_.getSize();
	}

	//gets the delta time 
	inline const float& Get_Elapsed_Time() const
	{
		return elapsed_time_;
	};

	//gets the event polled from the window
	inline sf::Event& Get_Event_()
	{
		return event_;
	};

	/*
	
	Utility functions

	*/

	//anything drawn to the screen is rendered
	inline void Render_()
	{
		window_.display();
		window_.clear(window_refresh_color_);
	};;

	//poll events for window
	void Update_();

	//draw a drawable to the window
	inline void Render_Window_Entity_(const sf::Drawable& entity_)
	{
		window_.draw(entity_);
	};

	//close the window
	inline void Close_Window_() { window_.close(); }

	void Set_Elapsed_Time_();

private:
	//CTORS & DTORS for window
	Window();
	~Window();

	//update delta time

	//window name
	const std::string window_name_ = "Snake";

	//window video mode
	sf::VideoMode window_video_mode_;

	//window
	sf::RenderWindow window_;

	//window refresh color
	const sf::Color window_refresh_color_ = sf::Color::Black;

	//window events
	sf::Event event_;

	//delta time
	float elapsed_time_ = 0.f;

	//window clock
	sf::Clock clock_;

};

#endif

