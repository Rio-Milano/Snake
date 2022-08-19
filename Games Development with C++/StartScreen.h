#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include<SFML/Graphics.hpp>

#include "Scene.h"
#include "Button.h"
#include "Animation.h"

/*

this class is a child class of scene and is initially scene when the game is loaded

*/

class StartScreen : public  Scene//inherits and implements scene
{
public:
	//ctors and dtors
	StartScreen();
	~StartScreen() = default;

	//draw the start screen widgets to the screen
	void Render_() override final;

	//update start screen widgets 
	void Update_() override final;

	//init the start screen
	void Init_() override final {};

	//deinit the start screen
	void De_Init_() override final;

private:
	//button to play game
	Button start_button_;

	//button to go to configure scene
	Button configure_button_;

	//button to close application
	Button exit_button_;

	//animation for the title 
	Animation snake_text_animation_;
		

};

#endif
