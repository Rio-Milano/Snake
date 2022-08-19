#include<SFML/Graphics.hpp>
#include"WhiteScene.h"

#include "StartScreen.h"

#include"SceneManager.h"
#define SceneManager  SceneManager::Instance_()


 StartScreen::StartScreen() : //init list to setup widgets 
	snake_text_animation_({ 1.75f, 1.75f }, { 10, 120 }, 50), //call the ctor for text animation
	start_button_({ 700, 510 }, "Start", { 820, 525 }, 100u, sf::Color(230, 238, 54)), //ctor for start button
	configure_button_({ 700, 710 }, "Configure", { 715, 725 }, 100u, sf::Color(230, 238, 54)),//ctor for configure button
	exit_button_({ 10, 970 }, "Exit", { 103, 985 }, 60u, sf::Color(230, 238, 54), { 330, 100 })
{}

void  StartScreen::Render_()
{
	//render start screen widgets 
	start_button_.Render();
	configure_button_.Render();
	snake_text_animation_.Render_();
	exit_button_.Render();
}

void  StartScreen::Update_()
{
	//update start screen widgets
	start_button_.Update();
	configure_button_.Update();
	exit_button_.Update();
	snake_text_animation_.Update_();

	//if the startr button is clicked
	if (start_button_.Get_Is_Clicked_())
	{
		//cast the  
		 Scene* scene_ = (dynamic_cast<WhiteScene*> (SceneManager.Peak_Scene_().get()));
		scene_ != nullptr ? SceneManager.Pop_Scene_() : void();

		SceneManager.Pop_Scene_();
		SceneManager.Load_Scene_("GameScene");
		SceneManager.Load_Scene_("WhiteScene");
	}


	if (configure_button_.Get_Is_Clicked_())
	{
		//cast the scene on top of the stack to the white scene
		Scene* scene_ = (dynamic_cast<WhiteScene*> (SceneManager.Peak_Scene_().get()));
		
		//if the white scene is present then take it off the stack
		scene_ != nullptr ? SceneManager.Pop_Scene_() : void();

		//pop the start screen scene
		SceneManager.Pop_Scene_();

		//load the configure scene
		SceneManager.Load_Scene_("ConfigureScene");

		//load the white screen
		SceneManager.Load_Scene_("WhiteScene");
	}
	//if the exit button is pressed then
	if(exit_button_.Get_Is_Clicked_())
	{
		//close the window
		Window.Close_Window_();
	}

}

void  StartScreen::De_Init_()
{
	//reset all window widgets 
	start_button_.Reset_Button_();
	configure_button_.Reset_Button_();
	exit_button_.Reset_Button_();
}

