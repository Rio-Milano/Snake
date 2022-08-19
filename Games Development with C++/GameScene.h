#ifndef GAMESCENE_H
#define GAMESCENE_

#include <SFML/Graphics.hpp>

#include "Scene.h"
#include"Snake.h"
#include"Collectable.h"
#include"Text.h"
#include"Button.h"
#include"ClockWidget.h"
#include"LeaderboardWidget.h"
#include"SlideBar.h"


/*
this class is a child of scene and represents the displaying and updating of the game itself
*/

class GameScene : public  Scene//inherits and implements scene
{
public:
	//ctors and dtors
	GameScene();
	~GameScene();

	//update the game
	void Update_() override final;

	//draw the game to the window
	void Render_() override final;

	//load the game
	void Init_() override final ;

	//unload the game
	void De_Init_() override final;

	//generate all of the points to use in a snake
	std::vector<sf::Vector2f> Build_Snake_();

	//add the generated points to a snake
	void Add_Segments_To_Snake_(const std::vector<sf::Vector2f>& points_,  std::shared_ptr<Snake>& snake_);

	//is a snake colliding with other snakes
	const bool Is_Colliding_With_Other_Snakes_(const std::vector<sf::Vector2f>& snake_points_);

	//is a point colliding with other things in the game
	const bool Check_Collision_With_Game_World_(const sf::Vector2f& pos_);

	//set is the game over 
	void Set_Game_Over_Status_() ;

	//generate the AI snakes for the game
	void Generate_AI_Snakes_();

	//generate the player snake
	void Generate_Player_Snake_();

	//generate the two player snake
	void Generate_Two_Player_Snake_();

	//generate the food
	void Generate_Food_();

	//check collision with snakes and food
	void Check_Collision_With_Food_(const std::shared_ptr<Collectable>& collectable_);
	
	//check collision with snakes and battery
	void Check_Collision_With_Battery_(const std::shared_ptr<Collectable>& collectable_);
	
	//generate battery collectables
	void Generate_Battery_();

	//vector to hold text objects that appear when a snake collects an item
	static std::list<Text> text_notifi_;

	//a vector to hold segments of detached snakes that can be collected by other snakes
	static std::list<sf::Vector2f> dead_segments_;


private:
	
	sf::Sprite dead_snake_texture_;

	//grid segment shape
	sf::RectangleShape grid_segment_;

	//size of grid segment shape
	const sf::Vector2f grid_segment_size_{ 40.f, 40.f };

	//grid points
	const sf::Vector2f top_left_grid_point_{ 440, 40 };
	const sf::Vector2f bottom_right_grid_point_{ 1440, 1040 };

	//game over flag
	bool is_game_over_ = false;

	//list of snakes
	std::vector<std::shared_ptr<Snake>> snakes_;

	//list of collectables 
	std::vector<std::shared_ptr<Collectable>> collectables_;

	//clock widget for count down
	ClockWidget clock_;

	//narrator restrictions 
	bool has_30_secconds_played_ = false;
	bool has_60_secconds_played_ = false;

	//grid image 
	sf::Sprite grid_overlay_;

	//pause button pauses game
	Button pause_button_;

	//paused flag
	bool game_paused_ = false;

	//menu button goes to menu
	Button menu_button_;
		
	//reset button resets game grid
	Button reset_button;

	//exit button closes game
	Button exit_button_;

	//leaderboard widget for ranking snakes
	LeaderboardWidget leaderboard_widget_;

};

#endif

