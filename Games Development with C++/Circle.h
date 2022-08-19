#ifndef CIRCLE_H
#define CIRCLE_H


#include <iostream>
#include<SFML/Graphics.hpp>
#include "Window.h"

/*

this circle is used for the animation of the background 

*/

struct Circle
{

	explicit Circle(const double& radius_) : radius_(radius_)//set variables 
	{
		//generate an x position
		x_pos = rand() % ( Window::Instance_().Get_Screen_Size_().x + 1);//random pos between start x and and X
		
		//out of window range checking 
		if (x_pos < radius_)
			x_pos = radius_;
		if (x_pos >  Window::Instance_().Get_Screen_Size_().x - radius_)// Game::Get_Game_Instance_().Get_Window_().Get_Screen_Size_().x
			x_pos =  Window::Instance_().Get_Screen_Size_().x - radius_;

		//generate a y position
		y_pos = rand() % ( Window::Instance_().Get_Screen_Size_().y + 1);//random pos between start y and end X
		
		//out of window range checking 
		if (y_pos < radius_)
			y_pos = radius_;
		if (y_pos >  Window::Instance_().Get_Screen_Size_().y - radius_)
			y_pos =  Window::Instance_().Get_Screen_Size_().y - radius_;

		//keep generating new positions until we get a valid one
		do { x_dir = ((rand() % 3) - 1) * (rand() % 101); } while (x_dir >= -50 && x_dir <= 50);
		do { y_dir = ((rand() % 3) - 1) * (rand() % 101); } while (y_dir >= -50 && y_dir <= 50);

		//keep generating random a value to depict how much the transparancy will change each update until it is valid
		do { transparancy_velocity_ = (rand() % 3) - 1; } while (transparancy_velocity_ == 0);

	}


	void Update()
	{
		//if the cirle is out of the window boundaries then invert the direction
		if (x_pos - radius_ < 0 && x_dir < 0 || x_pos + radius_ >=  Window::Instance_().Get_Screen_Size_().x - 2 * radius_ && x_dir > 0)//if colliding with horizontal
			x_dir = -x_dir;
		if (y_pos - radius_ < 0 && y_dir < 0 || y_pos + radius_ > Window::Instance_().Get_Screen_Size_().y - 2 * radius_ && y_dir > 0)//if colliding with vertical
			y_dir = -y_dir;

		//update position of circle
		x_pos += x_dir *  Window::Instance_().Get_Elapsed_Time();//Move circle
		y_pos += y_dir *  Window::Instance_().Get_Elapsed_Time();

		//update transparancy of circle
		if (transparancy_ == 0 && transparancy_velocity_ < 0)
			transparancy_velocity_ = -transparancy_velocity_;
		if (transparancy_ == 180 && transparancy_velocity_ > 0)
			transparancy_velocity_ = -transparancy_velocity_;


		transparancy_ += transparancy_velocity_;

	}

	//variables used to deciribe circle
	double x_pos, y_pos, x_dir, y_dir, radius_;

	//hold the current transparancy thats set randomly 
	unsigned char transparancy_ = rand() % 120;
	
	//variable to depict how much the transparancy will change each frame
	int transparancy_velocity_;


};
#endif