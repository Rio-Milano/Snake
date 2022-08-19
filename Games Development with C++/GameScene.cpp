#include "GameScene.h"
#include <string>

#include"SceneManager.h"
#define SceneManager  SceneManager::Instance_()

#include "TextureManager.h"
#define TextureManager  TextureManager::Instance_()

#include "SoundManager.h"
#define SoundManager  SoundManager::Instance_()

#include "Window.h"
#define Window  Window::Instance_()

#include "AppleCollectable.h"
#include"BatteryCollectable.h"
#include"AISnake.h"
#include"PlayerSnake.h"
#include"Two_PlayerSnake.h"
#include"GameEndScene.h"
#include"ConfigureScene.h"
#include"WhiteScene.h"
#include"Utils.h"

//init the text notif vector
std::list< Text>   GameScene::text_notifi_;

//init the dead segments vector
std::list<sf::Vector2f>  GameScene::dead_segments_;


//constructors and deconstructors
 GameScene::GameScene() :
	 //init the widgets 
	clock_({ 1580, 55 }, { 1640, 160 }, 90, 100, sf::Color(0, 0, 0, 200), sf::Color::White, 4, sf::Color::White),

	pause_button_({ 1635, 720 }, "||", { 1636 , 710 }, 100u, sf::Color::White, { 100, 100 }),

	menu_button_({ 40, 20 }, "Menu", { 123, 35 }, 60, sf::Color::White, { 330, 100 }),

	reset_button({ 1530, 900 }, "Reset", { 1613, 915 }, 60, sf::Color::White, { 330, 100 }),

	exit_button_({ 1530, 550 }, "Exit", { 1613, 565 }, 60u, sf::Color::White, {330, 100}),

	leaderboard_widget_({15, 170})
{
	//set grid attributes
	grid_segment_.setSize({ grid_segment_size_.x -1, grid_segment_size_.y-1});
	grid_segment_.setOutlineColor(sf::Color(255, 0, 0, 80));
	grid_segment_.setOutlineThickness(1);

	//get overlay of grid texture
	grid_overlay_.setTexture(TextureManager.Get_Texture_("Grid_Overlay_Texture_"));

	//set dead snake texture 
	dead_snake_texture_.setTexture(TextureManager.Get_Texture_("dead_snake"));

}
 GameScene::~GameScene()
{
}


void  GameScene::Update_()
{
	//if the game is over
	if (is_game_over_)
	{
		//if the game end scene is not on the scene stack
		if (SceneManager.Is_Scene_Active_("GameEndScene") == false)
		{
			//if the white scene is on the stack
			if (dynamic_cast<WhiteScene*>(SceneManager.Peak_Scene_().get()) != nullptr)
				//remove the white scene from the display stack
				SceneManager.Pop_Scene_();

			//reset reset button
			reset_button.Reset_Button_();

			//copy snakes into game end scene vector of snakes
			GameEndScreen::snakes_ = snakes_;

			//load game end scene
			SceneManager.Load_Scene_("GameEndScene");

			//load the white scene
			SceneManager.Load_Scene_("WhiteScene");

		}
	}
	//if the game is not over
	else
	{
			//update the pause button
			pause_button_.Update();

			//if the pause button is clicked
			if (pause_button_.Get_Is_Clicked_())
			{
				//toggle the game paused flag
				game_paused_ = !game_paused_;
				
				//if the paused flag is set
				if (game_paused_)
					//set the color of the pause button to green
					pause_button_.Set_Button_FillColor_(sf::Color::Green);
				else
					//set the color of the pause button to white
					pause_button_.Set_Button_FillColor_(sf::Color::White);
			}

			//update the menu button
			menu_button_.Update();

			//if the menu button is clicked 
			if (menu_button_.Get_Is_Clicked_())
			{
				//cast top of display stack to white scene
				Scene* is_click_animation_in_use_ = (dynamic_cast<WhiteScene*>(SceneManager.Peak_Scene_().get()));
				
				//if white scene is top of display stack
				if (is_click_animation_in_use_)
					//remove white scene from top of display stack
					SceneManager.Pop_Scene_();

				//reset reset button
				reset_button.Reset_Button_();

				//remove the game scene from stack
				SceneManager.Pop_Scene_();

				//load start scene
				SceneManager.Load_Scene_("StartScreen");

				//load white scene
				SceneManager.Load_Scene_("WhiteScene");
				return;
			}

			//update reset button
			reset_button.Update();

			//if reset button is clicked
			if (reset_button.Get_Is_Clicked_())
			{
				//deinit and init the scene
				De_Init_();
				Init_();

				//exit update
				return;
			}

			//update exit button
			exit_button_.Update();

			//if the exit button is clicked
			if (exit_button_.Get_Is_Clicked_())
			{
				//close the program
				Window.Close_Window_();
			}

			//if the game is not paused
			if (game_paused_ == false)
			{
				//if the player snake is alive then update it
				snakes_[0]->Get_Is_Snake_Alive_() ? snakes_[0]->Update_(snakes_, collectables_) : void();

				//if the player snake has started moving
				if (snakes_[0]->Get_Has_Snake_Started_Moving())
				{
					//loop through all collectables
					for (std::shared_ptr<Collectable>& collectale_ : collectables_)
					{
						//if collectable is food
						if (collectale_->Get_Collectable_Type_() == E_CollectableType::eFood)
							//check collsion with food
							Check_Collision_With_Food_(collectale_);
						
						//if the collectable is not food
						else if (collectale_->Get_Collectable_Type_() == E_CollectableType::eBattery)
							//check collision with battery
							Check_Collision_With_Battery_(collectale_);

						collectale_->Update_();
					}

					//add all the snakes as obsticles to the game grid
					for (unsigned int i = 0; i < snakes_.size(); i++)
						snakes_[i]->Get_Is_Snake_Alive_() ? snakes_[i]->AddObsticles() : void();


					//loop through all the snakes
					for (unsigned int i = 0; i < snakes_.size(); i++)
					{
						//if the snake is alive update the electric for that snake
						snakes_[i]->Get_Is_Snake_Alive_() ? snakes_[i]->Update_Electric_() : void();
						
						if(i > 0)//because we update snake[0] above here
							//update the snake
							snakes_[i]->Get_Is_Snake_Alive_() ? snakes_[i]->Update_(snakes_, collectables_) : void();
					}


					//remove all obsticles from grid
					snakes_[0]->Get_Pathfinding_Instance_().m_grid.ResetObsticles();

					//update game over flag
					Set_Game_Over_Status_();
					
					
					//if the clock timer has not started then start the clock count down
					clock_.Get_Is_Clock_Started_() == false ? clock_.Toggle_Clock_() : void();

					//if the clock has started then update the clock
					clock_.Get_Is_Clock_Started_() ? clock_.Update_Clock_() : void();

					//if the clock is in range of 60 secconds then
					if (clock_.Get_Time_Left_() > 59.f && clock_.Get_Time_Left_() < 61.f && has_60_secconds_played_ == false)
					{
						//set play 60s narrator sound
						has_60_secconds_played_ = true;

						//play the 60 secconds narrator sound
						SoundManager.Play_Sound_("60_secconds");
					}
					//if the clock is in range of 30 secconds then
					else if (clock_.Get_Time_Left_() > 29.f && clock_.Get_Time_Left_() < 31.f && has_30_secconds_played_ == false)
					{
						//set has played 30s narrator sound
						has_30_secconds_played_ = true;

						//play 30 secconds narrator sound
						SoundManager.Play_Sound_("30_secconds");
					};
				}
				//update the leaderboard 
				leaderboard_widget_.Update_(snakes_);
			}
	}
}

void  GameScene::Render_()
{
	//draw all grid segments 
	grid_segment_.setFillColor(sf::Color(30, 30, 30, 160));
	for (unsigned int i = static_cast<unsigned int>(top_left_grid_point_.y);
		i < static_cast<unsigned int>(bottom_right_grid_point_.y);
		i+=static_cast<unsigned int>(grid_segment_size_.y))
	{
		for (unsigned int j = static_cast<unsigned int>(top_left_grid_point_.x);
			j < static_cast<unsigned int>(bottom_right_grid_point_.x);
			j += static_cast<unsigned int>(grid_segment_size_.x))
		{
			grid_segment_.setPosition({float(j), float(i)});
			Window.Render_Window_Entity_(grid_segment_);
		}
	}

	//loop through all snakes
	for (unsigned int i = 0; i < snakes_.size(); i++)
	{
		//if the snake is alive
		if (snakes_[i]->Get_Is_Snake_Alive_())
		{
			//render the snake electric field
			snakes_[i]->Update_Electric_Field_();
		}
	}

	//render the grid overlay
	Window.Render_Window_Entity_(grid_overlay_);
	
	//loop through all snakes and render each one
	for (unsigned int i = 0; i < snakes_.size(); i++)
		snakes_[i]->Render_();

	for (const auto& dead_seg :dead_segments_)
	{
		dead_snake_texture_.setPosition(dead_seg);
		Window.Render_Window_Entity_(dead_snake_texture_);
	}

	//loop through all collectables and update them
	for (std::shared_ptr<Collectable>& collect : collectables_)
		collect->Render_();

	//loop through all text objects
	for (auto& text_ : text_notifi_)
		//render text object
		text_.Render_();

	//loop through all snakes
	for (const auto& snake_ : snakes_)
		//draw snake tags
		snake_->Get_Is_Snake_Alive_() ?		snake_->Draw_Tags_() : void();

	//render widgets
	clock_.Render_();
	pause_button_.Render();
	menu_button_.Render();
	reset_button.Render();
	exit_button_.Render();
	leaderboard_widget_.Render_();

}

const bool Check_Points_In_Points_(const std::vector<sf::Vector2f>& points_, const sf::Vector2f point_)
{
	//loop through all the points in points 
	for (const sf::Vector2f& point__ : points_)
	{
		//if the point in vector is same as point passed then
		if (point__ == point_)
			//return true for point is same as point passed
			return true;
	}
	//return false for point is not in points 
	return false;
}

//load the game
void  GameScene::Init_()
{
	//generate all the things the game needs
	Generate_Player_Snake_();

	Generate_Two_Player_Snake_();

	Generate_AI_Snakes_();

	Generate_Food_();

	Generate_Battery_();
}

//unload game assets
void  GameScene::De_Init_()
{
	//resetting all of game widgets, dependant variables and object pools 
	leaderboard_widget_.Reset_();

	snakes_[0]->global_snake_ID = -1;

	pause_button_.Reset_Button_();
	game_paused_ = false;

	menu_button_.Reset_Button_();
	exit_button_.Reset_Button_();

	

	snakes_.clear();

	collectables_.clear();

	text_notifi_.clear();
	is_game_over_ = false;

	clock_.ResetClock();

	has_30_secconds_played_ = false;
	has_60_secconds_played_ = false;

	dead_segments_.clear();


}

//build the points for a snake
std::vector<sf::Vector2f>  GameScene::Build_Snake_()
{
	//define a start point
	sf::Vector2f point_;

	//keep generating a point
	do {
		point_ = Get_Grid_Point_({ 520, 120 }, sf::Vector2f(float(rand() % 22), float(rand() % 22)), grid_segment_size_);
	} while (!(point_.x >= 520 && point_.x < 1360 && point_.y >= 120 && point_.y < 960) || Check_Collision_With_Game_World_(point_) == true);
	//until point is valid

	//define a collection of points 
	std::vector<sf::Vector2f> generated_points_{ point_ };

	//define a  direction to generate points in
	Direction point_direction_{ Direction::eNone };


	int points_ = 2;//additional points needed

	//while not all points have been generated
	while (points_-- > 0)
	{
		//define a new point
		sf::Vector2f new_point_;

		//flag for unknown valid point
		bool new_point_valid_ = false;

		//while new point is not valid
		while (new_point_valid_ == false)
		{
			//new point = last generated point
			new_point_ = generated_points_[generated_points_.size() - 1];

			//get a random direction to move in
			Set_Direction_To_Random(point_direction_);

			//put direction into a switch
			switch (point_direction_)
			{
			//apply the direction to the new point
			case Direction::eUp:
				new_point_.y -= grid_segment_size_.y;
				break;
			case Direction::eDown:
				new_point_.y += grid_segment_size_.y;
				break;
			case Direction::eLeft:
				new_point_.x -= grid_segment_size_.x;
				break;
			default://right
				new_point_.x += grid_segment_size_.x;
			}
			//if the new point is not in conflict
			if (Check_Collision_With_Game_World_(new_point_) == false && Check_Points_In_Points_(generated_points_, new_point_) == false && point_.x >= 520 && point_.x <= 1360 && point_.y >= 120 && point_.y <= 960)
				//the new point is valid
				new_point_valid_ = true;
		}
		//add the new point to the generated points 
		generated_points_.emplace_back(new_point_);

	}
	//return the points generated 
	return generated_points_;
}

//function used for making snake
void  GameScene::Add_Segments_To_Snake_(const std::vector<sf::Vector2f>& generated_points_,  std::shared_ptr<Snake>& snake_)
{
	//add the initial point to the snake
	snake_->Set_Add_Segment_At_Point(
		generated_points_[0],
		generated_points_[0]);

	//loop through all other points in the snake
	for (unsigned int i = 1; i < generated_points_.size(); i++)
		//add the point to the snake
		snake_->Set_Add_Segment_At_Point(generated_points_[i], generated_points_[i - 1]);
}


const bool GameScene::Is_Colliding_With_Other_Snakes_(const std::vector<sf::Vector2f>& snake_points_)
{
	//loop through all snakes
	for (auto snake_ : snakes_)
	{
		//get the head of the current snake
		std::shared_ptr<SnakeSegment> head_ = snake_->Get_Snake_Head_();
		
		//loop through all segments of the current snake
		while (head_ != nullptr)
		{
			//loop through all points of the points passed
			for (const auto& snake_point_ : snake_points_)
			{
				//if the point is same as current snake segment pos
				if (snake_point_ == head_->Get_Pos_())
					//return true for conflict
					return true;
			}
			//move onto next segment
			head_ = head_->Get_Next_();
		}
	}
	//return false for no conflict 
	return false;
}

//check if position is causing conflict 
const bool  GameScene::Check_Collision_With_Game_World_(const sf::Vector2f& pos_)
{
	if (!(pos_.x >= 520 && pos_.x < 1360 && pos_.y >= 120 && pos_.y < 960))
		return true;

	//loop through all snakes
	for (const auto& snake_ : snakes_)
	{
		//if snake seg is colliding with pos
		if (snake_->Check_Collision_(pos_))
			return true;
	}

	//loop through all consumables
	for (const auto& consumable_ : collectables_)
	{
		//is collectable is alive and its position is is not free
		if (consumable_->Get_Pos_() == pos_ && consumable_->Get_Is_Alive_())
			return true;
	}

	for (const auto& dead_snake_segment_ : dead_segments_)
	{
		/*
		This ensures that apples or batterys cant spawn within a 1 tile radius of any dead segment
		*/
		sf::Vector2i closest_position_of_seg_ = static_cast<sf::Vector2i>(dead_snake_segment_);

		//topleft
		if (sf::Vector2i(static_cast<int>(closest_position_of_seg_.x - grid_segment_size_.x),
			static_cast<int>(closest_position_of_seg_.y - grid_segment_size_.y)) ==
							static_cast<sf::Vector2i>(pos_)) return true;
		//topmiddle
		if (sf::Vector2i(static_cast<int>(closest_position_of_seg_.x),
			static_cast<int>(closest_position_of_seg_.y - grid_segment_size_.y)) ==
							static_cast<sf::Vector2i>(pos_)) return true;

		//topright
		if (sf::Vector2i(static_cast<int>(closest_position_of_seg_.x + grid_segment_size_.x),
			static_cast<int>(closest_position_of_seg_.y - grid_segment_size_.y)) ==
							static_cast<sf::Vector2i>(pos_)) return true;


		//middle left
		if (sf::Vector2i(static_cast<int>(closest_position_of_seg_.x - grid_segment_size_.x),
			static_cast<int>(closest_position_of_seg_.y)) ==
							static_cast<sf::Vector2i>(pos_)) return true;

		//middle
		if (closest_position_of_seg_ == static_cast<sf::Vector2i>(pos_)) return true;

		//middleright
		if (sf::Vector2i(static_cast<int>(closest_position_of_seg_.x + grid_segment_size_.x),
			static_cast<int>(closest_position_of_seg_.y)) ==
							static_cast<sf::Vector2i>(pos_)) return true;


		//bottomleft
		if (sf::Vector2i(static_cast<int>(closest_position_of_seg_.x - grid_segment_size_.x),
			static_cast<int>(closest_position_of_seg_.y + grid_segment_size_.y)) ==
							static_cast<sf::Vector2i>(pos_)) return true;
		//bottommiddle
		if (sf::Vector2i(static_cast<int>(closest_position_of_seg_.x),
			static_cast<int>(closest_position_of_seg_.y + grid_segment_size_.y)) ==
							static_cast<sf::Vector2i>(pos_)) return true;

		//bottomright
		if (sf::Vector2i(	static_cast<int>(closest_position_of_seg_.x + grid_segment_size_.x),
							static_cast<int>(closest_position_of_seg_.y + grid_segment_size_.y)) ==
							static_cast<sf::Vector2i>(pos_)) return true;
	}
	//no collision 
	return false;
}

void  GameScene::Set_Game_Over_Status_() 
{
	//if the timer has finished
	if (clock_.Get_Is_Time_Over_() == true)
	{
		//game is over
		is_game_over_ = true;
		return;
	}

	//count for snakes alive
	int count_ = 0;

	//loop through all snakes
	for (const auto& snake_ : snakes_)
	{
		//if the snake is alive
		if (snake_->Get_Is_Snake_Alive_())
		{
			//+1 to count
			count_++;

			//if more than 2 snakes are alive
			if(count_ >= 2)
				//exit
				return;
		}
	}
	
	//if only player snake
	if (ConfigureScene::AI_On_ == false && ConfigureScene::P2_On_ == false)
	{
		//if player snake is alive
		if (snakes_[0]->Get_Is_Snake_Alive_())
			//exit
			return;
	}

	//game is over
	is_game_over_ = true;
}

void  GameScene::Generate_AI_Snakes_()
{
	//if AI was turned on in config menu
	if (ConfigureScene::AI_On_ == true)
	{
		int i = 3;//3 snakes to generate
		
		//while all snakes have not been generated 
		while (i-- > 0)
		{
			//make a new snake object on heap
			std::shared_ptr<Snake> snake_ = std::make_shared<AISnake>(top_left_grid_point_, bottom_right_grid_point_, "AI");
				
			//build the points for a snake
			std::vector<sf::Vector2f> generated_points_ = Build_Snake_();

			//add the points generated to the snake
			Add_Segments_To_Snake_(generated_points_, snake_);

			//push the generated snake to the snakes vector
			snakes_.emplace_back(snake_);
		};
	}
}

//add player snake to game
void  GameScene::Generate_Player_Snake_()
{
	//define new snake
	std::shared_ptr<Snake> snake_ = std::make_shared<PlayerSnake>(top_left_grid_point_, bottom_right_grid_point_, "P1");

	//build snake points
	std::vector<sf::Vector2f> generated_points_ = Build_Snake_();

	//add the points to the snake
	Add_Segments_To_Snake_(generated_points_, snake_);

	//add the snake to the game snakes
	snakes_.emplace_back(snake_);
}

//add the two player snake
void  GameScene::Generate_Two_Player_Snake_()
{
	//if 2 player snake was turned on in the configure menu
	if (ConfigureScene::P2_On_ == true)
	{
		//define a new snake
		std::shared_ptr<Snake> snake_ = std::make_shared<Two_PlayerSnake>(top_left_grid_point_, bottom_right_grid_point_, "P2");

		//make the points for the snake
		std::vector<sf::Vector2f> generated_points_ = Build_Snake_();

		//add the points to the snake
		Add_Segments_To_Snake_(generated_points_, snake_);

		//add the snake to the game snakes
		snakes_.emplace_back(snake_);
	}

}

//make the food for the snakes
void  GameScene::Generate_Food_()
{
	//define a point for position
	sf::Vector2f collectable_point_;

	//generate 7 food items
	int points_ = 7;

	//while have not generated 7 food items
	while (points_-- > 0)
	{
		//while point is colliding with a snake segment or another collectable point
		do
		{
			//get a new point
			collectable_point_ = Get_Grid_Point_();
		} while (Check_Collision_With_Game_World_(collectable_point_));
			
	
		//once point is valid add the point as a new apple collectable
		collectables_.emplace_back(std::make_shared<AppleCollectable>(AppleCollectable(collectable_point_)));
	}
}

//check if snakes are colliding with food item 
void  GameScene::Check_Collision_With_Food_(const std::shared_ptr<Collectable>& collectale_)
{
	//loop through all the snakes and check if they are colliding witht the collectable
	for (const auto& snake_ : snakes_)
	{
		//if snake destination is same as position of collectable and collectable is alive
		if (snake_->Get_Snake_Dest_() == collectale_->Get_Pos_() && collectale_->Get_Is_Alive_())
		{
			//increase the snake score by the food value
			snake_->Set_Increase_Snake_Score_(collectale_->Get_Food_Value_());

			//cast the snake to a player snake
			PlayerSnake* player_snake_ =dynamic_cast<PlayerSnake*> (snake_.get());

			//if the cast was successful
			if (player_snake_)
				//play sound for collecting food
				SoundManager.Play_Sound_("FoodCollection");


			//text object with score is created
			text_notifi_.push_back(Text("+"+std::to_string(collectale_->Get_Food_Value_()), snake_->Get_Snake_Dest_()));

			//make the snake bigger
			 snake_->Extend_Snake_(collectale_->Get_Food_Value_());

			//the collectable is collected
			collectale_->Set_Is_Alive(false);

			//collectable timer is initialised
			collectale_->Set_Time_Till_Spawn_();

		}
	}

	//if the timer is finished for food
	if (!collectale_->Get_Is_Alive_() && collectale_->Get_Time_Till_Spawn_() <= 0)
	{
		//generate a new point
		sf::Vector2f point_;

		//while point is invalid
		do {

				//get new point
				point_ = Get_Grid_Point_();
		} while (Check_Collision_With_Game_World_(point_));
		
		

		//when point is valid update point and make alive again
		collectale_->Set_Pos_(point_);
		collectale_->Set_Is_Alive(true);
	}

}


void  GameScene::Check_Collision_With_Battery_(const std::shared_ptr<Collectable>& collectable_)
{
	//loop through all the snakes and check if they are colliding witht he collectable
	for (const auto& snake_ : snakes_)
	{
		if (snake_->Get_Snake_Dest_() == collectable_->Get_Pos_() && collectable_->Get_Is_Alive_())
		{
			//players score is inceased
			snake_->Set_Increase_Snake_Score_(collectable_->Get_Food_Value_());

			PlayerSnake* player_snake_ = dynamic_cast<PlayerSnake*> (snake_.get());

			if (player_snake_)
				SoundManager.Play_Sound_("ElectricSoundEffect");

				//text object for players score is updated

			snake_->Extend_Snake_(collectable_->Get_Food_Value_());

			//text object with score is created
			text_notifi_.push_back(Text("+"+std::to_string(collectable_->Get_Food_Value_()), snake_->Get_Snake_Dest_()));

			//enable battery mode for snake
			snake_->Activate_Battery_();
			
			//define a new point
			sf::Vector2f point_;

			//while point is invalid
			do {
				point_ = Get_Grid_Point_();
			} while (Check_Collision_With_Game_World_(point_));
				//generate a new point

			//when point is valid update point and make alive again
			collectable_->Set_Pos_(point_);

		}
	}

}

//make batteries for game
void  GameScene::Generate_Battery_()
{
	//define a point
	sf::Vector2f collectable_point_;


	int points_{ 1 };//1 battery for game

	//while have not generated all points 
	while (points_-- > 0)
	{
		do
		{
			//generate point
			collectable_point_ = Get_Grid_Point_();
		}
		while (Check_Collision_With_Game_World_(collectable_point_));
		
		//add battery to collectables
		collectables_.emplace_back(new BatteryCollectable(collectable_point_));
	}
}
