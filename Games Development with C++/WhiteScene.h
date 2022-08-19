#ifndef WHITESCENE_H
#define WHITESCENE_H

#include"Scene.h"
#include"Window.h"
#define Window Window::Instance_()

#include<SFML/Graphics.hpp>

/*

The white scene is a scene overlay that puts a fade over the new scene when loading it 

*/

class WhiteScene : public  Scene//inherits and implements from scene 
{
public:

	WhiteScene();
	~WhiteScene() = default;

	//draw the effect to the window
	inline void Render_() override final
	{
		Window.Render_Window_Entity_(white_shape_overlay);
	};

	//update the white scene
	void Update_() override final;

	//load the whitescene
	inline void Init_() override final;

	//unload the white scene
	void De_Init_() override final;

	

private:
	//shape used for the white effect
	sf::RectangleShape white_shape_overlay;

	//keeps track of the opacity of the effect
	int current_screen_opacity_{255u};

	//hold the rate of change for the opacity 
	int color_change_velocity_{-4};



};

#endif

