#include "LeaderboardWidget.h"

#include"TextureManager.h"
#define TextureManager  TextureManager::Instance_()


#include"Window.h"
#define Window Window::Instance_()

#include"PlayerSnake.h"
#include"Two_PlayerSnake.h"

#include"ConfigureScene.h"

//macro for max progress bar size
#define MAX_PROGRESS_BAR_SIZE float {560.f}

//macro for min progress bar size
#define MIN_PROGRESS_BAR_SIZE float {50.f}

LeaderboardWidget::LeaderboardWidget(const sf::Vector2f& position_)
//init list to set up widgets
	:snake_1_text_("P1", { position_.x + 115.f, position_.y + 60 }, 0, 0, 20U, sf::Color::Black),
	snake_2_text_("AI", { position_.x + 275.f, position_.y + 60 }, 0, 0, 20U, sf::Color::Black),
	snake_1_progress_bar_value_text_("0+", { 120, 300 }, 0, 0, 30u, sf::Color::White),
	snake_2_progress_bar_value_text_("0+", { 280, 300 }, 0, 0, 30U, sf::Color::White)
{
	//set up background shape
	white_shape_.setFillColor(sf::Color(255u, 255u, 255u, 220));
	white_shape_.setSize({ 380, 200 });
	white_shape_.setPosition(position_);

	//set up snake sprite 1 
	snake_1_sprite.setTexture(TextureManager.Get_Texture_("Player_Head_Texture"));
	snake_1_sprite.scale({ 2, 2 });
	snake_1_sprite.rotate(180.f);
	snake_1_sprite.setPosition(position_.x + 140, position_.y + 160);

	//set up snake sprite 12
	snake_2_sprite.setTexture(TextureManager.Get_Texture_("A_Default_Head_Texture"));
	snake_2_sprite.scale({ 2, 2 });
	snake_2_sprite.rotate(180.f);
	snake_2_sprite.setPosition(position_.x + 300, position_.y + 160);

	//setup snake 1 progress bar
	snake_1_progress_bar_.setPosition(78, snake_1_sprite.getPosition().y + 40);
	snake_1_progress_bar_.setSize({80, 50});
	snake_1_progress_bar_.setFillColor(sf::Color(0, 160, 120));

	//setup snake 2 progress bar
	snake_2_progress_bar_.setPosition(237, snake_1_sprite.getPosition().y + 40);
	snake_2_progress_bar_.setSize({ 80, 50 });
	snake_2_progress_bar_.setFillColor(sf::Color(77, 0, 10));
}

 void LeaderboardWidget::Render_()
{
	 //if AI snakes or player 2 is enabled 
	 if (ConfigureScene::AI_On_ || ConfigureScene::P2_On_)
	 {
		 //draw all the widgets

		 Window.Render_Window_Entity_(white_shape_);

		 Window.Render_Window_Entity_(snake_1_sprite);
		 snake_1_text_.Render_();

		 Window.Render_Window_Entity_(snake_2_sprite);
		 snake_2_text_.Render_();

		 Window.Render_Window_Entity_(snake_1_progress_bar_);
		 Window.Render_Window_Entity_(snake_2_progress_bar_);

		 
		 snake_1_progress_bar_value_text_.Render_();
		 snake_2_progress_bar_value_text_.Render_();

	}
}

 void LeaderboardWidget::Update_(std::vector< std::shared_ptr<Snake>> snakes_)
 {
	 if (ConfigureScene::AI_On_ || ConfigureScene::P2_On_)
	 {
		 //pass in the snakes by value so sorting does not effect the ordering of the snakes

		 //sort the snakes using a lambda function
		 std::sort(snakes_.begin(), snakes_.end(), [](const std::shared_ptr<Snake>& a, const std::shared_ptr<Snake>& b) -> bool {return a->Get_Snake_Score_() > b->Get_Snake_Score_(); });
		 
		 //set the snake in first and seccond place
		 snake_in_first_place_ = snakes_[0];
		 snake_in_seccond_place_ = snakes_[1];

		 //define a shared 

		 //cast snake in first place to different types to get the actual type then use that to set the snake text for name
		 if (dynamic_cast< PlayerSnake*>(snake_in_first_place_.get()) != nullptr)
			 snake_1_text_.Set_Text_("P1");
		 else if (dynamic_cast<Two_PlayerSnake*>(snake_in_first_place_.get()) != nullptr)
			 snake_1_text_.Set_Text_("P2");
		 else
			 snake_1_text_.Set_Text_("AI." + std::to_string(snake_in_first_place_->snake_ID));

		 //cast snake in seccond place to different types to get the actual type then use that to set the snake text for name
		 if (dynamic_cast<PlayerSnake*>(snake_in_seccond_place_.get()) != nullptr)
			 snake_2_text_.Set_Text_("P1");
		 else if (dynamic_cast<Two_PlayerSnake*>(snake_in_seccond_place_.get()) != nullptr)
			 snake_2_text_.Set_Text_("P2");
		 else
			 snake_2_text_.Set_Text_("AI." + std::to_string(snake_in_seccond_place_->snake_ID));



		 //set the sprite for the first progress bar
		 if (snake_in_first_place_->Get_Is_Snake_Alive_() == false)
			 snake_1_sprite.setTexture(TextureManager.Get_Texture_(snake_in_first_place_->Get_Snake_Head_Name_() + "DEAD"));
		 else
			 snake_1_sprite.setTexture(TextureManager.Get_Texture_(snake_in_first_place_->Get_Snake_Head_Name_()));

		 //set the size of the first progress bar
		 snake_1_progress_bar_.setSize
		 ({
			  snake_1_progress_bar_.getSize().x,
			  MIN_PROGRESS_BAR_SIZE + ((static_cast<float>(snake_in_first_place_->Get_Snake_Score_()) / 100) * MAX_PROGRESS_BAR_SIZE)
			 });

		 //set the position of the snake 1 value text
		 snake_1_progress_bar_value_text_.Set_Position_
		 ({
			 snake_1_progress_bar_value_text_.getPosition().x,
			 snake_1_progress_bar_.getPosition().y + snake_1_progress_bar_.getSize().y + 40
			 });

		 //set the text for the snake 1 progress bar
		 snake_1_progress_bar_value_text_.Set_Text_(std::to_string(snake_in_first_place_->Get_Snake_Score_()) + "+");

		


		 //set the sprite for the seccond progress bar
		 if (snake_in_seccond_place_->Get_Is_Snake_Alive_() == false)
			 snake_2_sprite.setTexture(TextureManager.Get_Texture_(snake_in_seccond_place_->Get_Snake_Head_Name_() + "DEAD"));
		 else
			 snake_2_sprite.setTexture(TextureManager.Get_Texture_(snake_in_seccond_place_->Get_Snake_Head_Name_()));

		 //set the size of the seccond progress bar
		 snake_2_progress_bar_.setSize
		 ({
			  snake_2_progress_bar_.getSize().x,
			  MIN_PROGRESS_BAR_SIZE + ((static_cast<float>(snake_in_seccond_place_->Get_Snake_Score_()) / 100) * MAX_PROGRESS_BAR_SIZE)
			 });

		 //set the position of the snake 2 value text
		 snake_2_progress_bar_value_text_.Set_Position_
		 ({
			 snake_2_progress_bar_value_text_.getPosition().x,
			 snake_2_progress_bar_.getPosition().y + snake_2_progress_bar_.getSize().y + 40
			 });

		 //set the text for the snake 2 progress bar
		 snake_2_progress_bar_value_text_.Set_Text_(std::to_string(snake_in_seccond_place_->Get_Snake_Score_()) + "+");
	 }
 }

 void LeaderboardWidget::Reset_()
 {
	 //reset snake in 1st and seccond place
	 snake_in_first_place_ = nullptr;
	 snake_in_seccond_place_ = nullptr;
 };
