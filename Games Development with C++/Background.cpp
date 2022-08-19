#include "Background.h"

#include "Window.h"
#define Window  Window::Instance_()

#include"TextureManager.h"
#define TextureManager  TextureManager::Instance_()


//ctors
 Background::Background()
{
	 //load the background image
	TextureManager.Load_Texture_Into_Memory_("Assets_/Textures_/Overlays_/BG_", ".jpg", "Background_IMG");
	
	//load the animation for the title
	TextureManager.Load_Animation_Into_Memory("Assets_/Textures_/Animations_/Title_Animation_/frame-", ".png", "SnakeStartAnim", size_t(50));

	
	//set the sprite to the background image
	cover_image_sprite_.setTexture(TextureManager.Get_Texture_("Background_IMG"));

	//set single circle pool object data
	circleShape.setRadius(static_cast<const float>(circleRadiusSize));
	circleShape.setFillColor(sf::Color(255, 255, 255, 25));
	
	//create all the circles to use
	Create_Circle_Array_();
}

//utility functions
void  Background::Render_()
{
	//render the background 
	Window.Render_Window_Entity_(cover_image_sprite_);
	
	//rennder all circles 
	for (const Circle& circle : listOfCircles)
	{
		circleShape.setPosition(sf::Vector2f(float(circle.x_pos), float(circle.y_pos)));
		circleShape.setFillColor(sf::Color(255, 255, 255, circle.transparancy_));
		Window.Render_Window_Entity_(circleShape);
	}
}

void  Background::Update_()
{
	//update all circles
	for (Circle& circle : listOfCircles)
		circle.Update();

}

//private utilioty functions
void  Background::Create_Circle_Array_()
{
	//create the vector  of circles 
	for (int i = 0; i < circleArraySize; i++)
	{
		listOfCircles.emplace_back(Circle(circleRadiusSize));
	}
}




