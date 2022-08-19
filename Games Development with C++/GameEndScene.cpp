#include "GameEndScene.h"

#include"WhiteScene.h"
#include"GameScene.h"
#include"PlayerSnake.h"
#include"Two_PlayerSnake.h"
#include"AISnake.h"
#include"ConfigureScene.h"

#include "SceneManager.h"
#define SceneManager  SceneManager::Instance_()

#include "Window.h"
#define Window  Window::Instance_()

#include"TextureManager.h"
#define TextureManager  TextureManager::Instance_()

//init the static vector for snakes
std::vector< std::shared_ptr<Snake>>  GameEndScreen::snakes_ = {};

 GameEndScreen::GameEndScreen() : //init list to setup widgets 
	main_menu_button_(sf::Vector2f( 670.f,  20.f ),	"Main Menu", sf::Vector2f(760.f,33.f), 60u, sf::Color::Yellow,	{500, 94}),

	exit_button_({ 10, 20 }, "Exit", { 103, 33 }, 60u, sf::Color(230, 238, 54), { 330, 100 }),
	
	snake_in_first_place_text_("", { 887, 439 }, 0, 0, 30, sf::Color::Black),

	snake_in_seccond_place_text_("", { 352, 530 }, 0, 0, 30, sf::Color::Black),

	snake_in_third_place_text_("", {1390, 563}, 0, 0, 30, sf::Color::Black)

{
	//set texture for distorted image
	game_over_overlay_.setTexture(TextureManager.Get_Texture_("Background_IMG"));

	//reduce opacity for distorted image
	game_over_overlay_.setColor(sf::Color(game_over_overlay_.getColor().r, game_over_overlay_.getColor().g, game_over_overlay_.getColor().b, 180));
	
	//set texture for podium
	podium_texture_.setTexture(TextureManager.Get_Texture_("Podium_Texture"));

	//set positions of snake textures on podium 
	snake_in_first_place_spr.setPosition(862, 527);
	snake_in_seccond_place_spr.setPosition(337, 625);
	snake_in_third_place_spr.setPosition(1359, 663);

}

void  GameEndScreen::Render_()
{
	//draw all widgets to the window
	Window.Render_Window_Entity_(game_over_overlay_);
	Window.Render_Window_Entity_(podium_texture_);
	
	main_menu_button_.Render();
	exit_button_.Render();

	Window.Render_Window_Entity_(snake_in_first_place_spr);
	snake_in_first_place_text_.Render_();

	//if there is more than one snake then draw the snake in seccond place set
	if (snakes_.size() > 1)
	{
		Window.Render_Window_Entity_(snake_in_seccond_place_spr);
		snake_in_seccond_place_text_.Render_();
	}

	//if there is more than 2 snakes then draw then snake in third place set
	if (snakes_.size() > 2)
	{
		Window.Render_Window_Entity_(snake_in_third_place_spr);
		snake_in_third_place_text_.Render_();
	}
}

void  GameEndScreen::Update_()
{
	//update main menu button
	main_menu_button_.Update();

	//if the main menu button is clicked
	if (main_menu_button_.Get_Is_Clicked_())
	{
		//if the white scene is still active then remove it
		if (dynamic_cast<WhiteScene*>(SceneManager.Peak_Scene_().get()) != nullptr)
			SceneManager.Pop_Scene_();
			
			//pop the game end scene
			SceneManager.Pop_Scene_();

			//pop the game scene
			SceneManager.Pop_Scene_();
		
			//load the start screen
			SceneManager.Load_Scene_("StartScreen");

			//load the white animation
			SceneManager.Load_Scene_("WhiteScene");

			//exit function
			return;
	}

	//update the exit button
	exit_button_.Update();
	
	//if exit button is clicked
	if (exit_button_.Get_Is_Clicked_())
	{
		//close game
		Window.Close_Window_();
	}


	 std::shared_ptr<Snake> snake_in_first_place_;
	 std::shared_ptr< Snake> snake_in_seccond_place_;
	 std::shared_ptr<Snake> snake_in_third_place_;

	//if there is more than one snake
	if (snakes_.size() > 0)
	{
		//use a lambda function to sort the list
		std::sort((snakes_).begin(), (snakes_).end(),
			[](const std::shared_ptr<Snake> a, const std::shared_ptr<Snake> b) -> bool
			{
				return a->Get_Snake_Score_() > b->Get_Snake_Score_();
			});
	}

	//set the snake in first place 
	snake_in_first_place_ = (snakes_)[0];

	//if more than 1 snake
	if (snakes_.size() > 1)
	{
		//set snake in seccond place 
		snake_in_seccond_place_ = (snakes_)[1];
	}

	//if more than 2 snakes
	if (snakes_.size() > 2)
	{
		//set snake in third place
		snake_in_third_place_ = (snakes_)[2];
	}

	//set snake in first place set data
	snake_in_first_place_spr.setTexture(TextureManager.Get_Texture_(snake_in_first_place_->Get_Snake_Head_Name_()));
	snake_in_first_place_spr.setScale(5, 5);

	//if more than one snake
	if (snakes_.size() > 1)
	{
		//set snake in seccond set data
		snake_in_seccond_place_spr.setTexture(TextureManager.Get_Texture_(snake_in_seccond_place_->Get_Snake_Head_Name_()));
		snake_in_seccond_place_spr.setScale(5, 5);
	}

	//if more than 2 snakes
	if (snakes_.size() > 2)
	{
		//set snake in seccond set data
		snake_in_third_place_spr.setTexture(TextureManager.Get_Texture_(snake_in_third_place_->Get_Snake_Head_Name_()));
		snake_in_third_place_spr.setScale(5, 5);
	}


	//try to cast snake in first place to different types and when successful set the text widget for the name of snake 1
	if (dynamic_cast<PlayerSnake*>(snake_in_first_place_.get()) != nullptr)
		snake_in_first_place_text_.Set_Text_("P1: " + std::to_string(snake_in_first_place_->Get_Snake_Score_()));
	else if (dynamic_cast<Two_PlayerSnake*>(snake_in_first_place_.get()) != nullptr)
		snake_in_first_place_text_.Set_Text_("P2: " + std::to_string(snake_in_first_place_->Get_Snake_Score_()));
	else if (dynamic_cast<AISnake*>(snake_in_first_place_.get()) != nullptr)
		snake_in_first_place_text_.Set_Text_("AI." + std::to_string(snake_in_first_place_->snake_ID) + ": " + std::to_string(snake_in_first_place_->Get_Snake_Score_()));

	//if more than 1 snake
	if (snakes_.size() > 1)
	{
		//try to cast snake in seccond place to different types and when successful set the text widget for the name of snake 2
		if (dynamic_cast<PlayerSnake*>(snake_in_seccond_place_.get()) != nullptr)
			snake_in_seccond_place_text_.Set_Text_("P1: " + std::to_string(snake_in_seccond_place_->Get_Snake_Score_()));
		else if (dynamic_cast<Two_PlayerSnake*>(snake_in_seccond_place_.get()) != nullptr)
			snake_in_seccond_place_text_.Set_Text_("P2: " + std::to_string(snake_in_seccond_place_->Get_Snake_Score_()));
		else if (dynamic_cast<AISnake*>(snake_in_seccond_place_.get()) != nullptr)
			snake_in_seccond_place_text_.Set_Text_("AI." + std::to_string(snake_in_seccond_place_->snake_ID) + ": " + std::to_string(snake_in_seccond_place_->Get_Snake_Score_()));
	}

	//if more than 2 snakes
	if (snakes_.size() > 2)
	{
		//try to cast snake in third place to different types and when successful set the text widget for the name of snake 3
		if (dynamic_cast<PlayerSnake*>(snake_in_third_place_.get()) != nullptr)
			snake_in_third_place_text_.Set_Text_("P1: " + std::to_string(snake_in_third_place_->Get_Snake_Score_()));
		else if (dynamic_cast<Two_PlayerSnake*>(snake_in_third_place_.get()) != nullptr)
			snake_in_third_place_text_.Set_Text_("P2: " + std::to_string(snake_in_third_place_->Get_Snake_Score_()));
		else if (dynamic_cast<AISnake*>(snake_in_third_place_.get()) != nullptr)
			snake_in_third_place_text_.Set_Text_("AI." + std::to_string(snake_in_third_place_->snake_ID) + ": " + std::to_string(snake_in_third_place_->Get_Snake_Score_()));

	}
	
}

void  GameEndScreen::De_Init_()
{
	//reset buttons
	main_menu_button_.Reset_Button_();
	exit_button_.Reset_Button_();
}
