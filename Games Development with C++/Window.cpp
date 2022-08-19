#include "Window.h"

//Constructors & Decostructors
 Window::Window()
	:window_(window_video_mode_, window_name_, sf::Style::Fullscreen)
{
	window_.setVerticalSyncEnabled(1);
};
 Window::~Window()
{
};

//getter functions
 Window& Window::Instance_()
{
	 //a single instance of winow
	static Window window_;

	//return ins
	return window_;
}


//utility functions

void Window::Update_()
{
	//poll event
	while (window_.pollEvent(event_))
	{
		//switch to decode events
		switch (event_.key.code)
		{
		//if escape is pressed then close the window
		case sf::Keyboard::Escape:
			window_.close();
			break;
		}
	}

}


//private utility functions
void Window::Set_Elapsed_Time_()
{
	//set elapsed time to delta time
	elapsed_time_ = clock_.getElapsedTime().asSeconds();

	//reset the clock
	clock_.restart();
}


