#ifndef BACKGROUND_H
#define BACKGROUND_H

#include"Scene.h"
#include"Circle.h"

#include<vector>
/*

Background is the lowest scene in the stack that is an image and moving circles

*/
	class Background : public  Scene//background implements scene
	{
	public:
		//ctors and dtors
		Background();
		~Background() = default;

		/*
		utility functions
		*/
		
		//draw then scene to the window
		void Render_() override final;

		//update the scene
		void Update_() override final;

		//load all of the scenes content 
		void Init_() override final {};

		//unload all of the scenes content 
		void De_Init_() override final {};
		


	private:
		//create all of the circles the window uses
		void Create_Circle_Array_();

		//sprite for the cover image
		sf::Sprite cover_image_sprite_;

		//single object pool used for drawing circles
		sf::CircleShape circleShape;

		//amount of circles to use
		const int circleArraySize{ 300 };

		//radius for all circles
		const double circleRadiusSize{ 5};

		//a list of all the circle data
		std::vector<Circle> listOfCircles;
	};

#endif

