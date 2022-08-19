#ifndef SNAKE_H
#define SNAKE_H

#include<SFML/Graphics.hpp>
#include <vector>

#include "Direction.h"
#include "SnakeSegment.h"
#include"DoublyLinkedList.h"
#include"Collectable.h"
#include"PathFinding.h"
#include<iostream>
#include"Text.h"
#include<utility>
#include<list>

/*
this class is the base class for all the snakes in the game
*/

class Snake
{
public:
	//used for initial setup for grid position locking in path finding
	static int global_snake_ID;
	
	//individial snake IDs
	int snake_ID{ -1 };

	//ctos and dtors
	explicit Snake(const sf::Vector2f& top_left_grid_point_, const sf::Vector2f& bottom_right_grid_point_, const std::string& snake_name_);
	~Snake() = default;

	///===MAIN FUNCTIONS======MAIN FUNCTIONS======MAIN FUNCTIONS======MAIN FUNCTIONS======MAIN FUNCTIONS======MAIN FUNCTIONS======MAIN FUNCTIONS===///

	//pure virtual functions

	//get the input for the snake to decide direction 
	virtual void Class_Input_( std::vector< std::shared_ptr<Collectable>>& collectables_) = 0;

	//update the snake
	void Update_(const std::vector<std::shared_ptr<Snake>>& snakes_,  std::vector< std::shared_ptr<Collectable>>& collectables_);

	///draw the snake to the window
	void Render_();

	//draw the field arround the snake
	void Draw_Electric_Field_(const sf::Color& color_ = sf::Color(255, 255, 255, 2));

	//logic behind what type of field to draw
	void Update_Electric_Field_();


	//add N segments to the snake
	void Extend_Snake_(int n);

	//check if a point on the grid is colliding with any snake segment position
	bool Check_Collision_(const sf::Vector2f& pos_);

	//if the snake is in its electric state then update that state
	void Update_Electric_();

	//remove segments after and including a point
	int Remove_Segments_( std::shared_ptr<SnakeSegment>remove_segment_);

	//draw the snake name tags
	void Draw_Tags_();

	///===MAIN FUNCTIONS======MAIN FUNCTIONS======MAIN FUNCTIONS======MAIN FUNCTIONS======MAIN FUNCTIONS======MAIN FUNCTIONS======MAIN FUNCTIONS===///



	///===MANIPULATION=========MANIPULATION=========MANIPULATION=========MANIPULATION=========MANIPULATION=========MANIPULATION======///

	//activate the battery collection state
	inline void Activate_Battery_() { this->isElectric_ = true;	/**/ this->time_left_for_electric_ = this->max_time_left_for_electric_; };

	//reset all the snakes attributes (for de-init scenes)
	void Reset_Snake_();

	// add snake segments to the the grid used in pathfinding
	void AddObsticles();

	//Interpolate the snake between positions
	void Move_Snake_();

	///===MANIPULATION=========MANIPULATION=========MANIPULATION=========MANIPULATION=========MANIPULATION=========MANIPULATION======///



	///===GETTERS======GETTERS======GETTERS======GETTERS======GETTERS======GETTERS======GETTERS======GETTERS======GETTERS======GETTERS===///

	//gets the 1 instace of the pathfinding obj
	PathFinding& Get_Pathfinding_Instance_() const { static PathFinding path_finding_; return path_finding_; };

	//get the snake head and body textures in the form of a pair (head, body) str, str
	inline const std::string& Get_Snake_Head_Name_()const { return snake_head_texture_name; };

	//get the head of the snake
	inline std::shared_ptr<SnakeSegment> Get_Snake_Head_() const{ return this->list_of_segments.Get_Head_(); }

	//get the position of the snake head
	inline const sf::Vector2f& Get_Snake_Pos_() const{ return list_of_segments.Get_Head_()->Get_Pos_(); };

	//Get the snake destination of the snake head
	inline const sf::Vector2f& Get_Snake_Dest_() const{ return list_of_segments.Get_Head_()->Get_Dest_(); };

	//Get is the snake alive
	inline const bool Get_Is_Snake_Alive_() const { return !snake_dead_; };

	//Get the snake score
	inline const int Get_Snake_Score_()const { return this->score_; };

	//get if the snake has started moving
	inline const bool& Get_Has_Snake_Started_Moving() const { return this->is_direction_set_; }

	//get if the snake is electric
	inline const bool& Get_Is_Snake_Electric()const { return this->isElectric_; }

	//gets all the positions in the electric field
	inline const std::vector<sf::Vector2f>& Get_Electric_Field_() { return this->electric_field_; }

	//get snake direction
	inline Direction Get_Direction() const{return direction_queue;};

	///===GETTERS======GETTERS======GETTERS======GETTERS======GETTERS======GETTERS======GETTERS======GETTERS======GETTERS======GETTERS===///




	///===SETTERS======SETTERS======SETTERS======SETTERS======SETTERS======SETTERS======SETTERS======SETTERS======SETTERS======SETTERS===///

	//set is snake dead
	inline void Set_Is_Snake_Dead_(const bool& snake_dead_status_) { this->snake_dead_ = snake_dead_status_; };

	//set the electrified state
	inline void Set_Snake_Is_Electrified_(const bool& set_) { this->isElectric_ = set_; }

	//increase the snake score by a given amount
	inline void Set_Increase_Snake_Score_(const int& points_) { this->score_ += points_; }

	//add a segment at a point (used for generating a snake)
	inline void Set_Add_Segment_At_Point(const sf::Vector2f& point_, const sf::Vector2f& point_vector_) { list_of_segments.Add_Segment_At_Point_(point_, point_, point_vector_); };

	//make the field that appears arround the snake
	void Set_Electric_Field_();

	//change direction of snake bassed on rules
	void Change_Direction_(const Direction& direction_);
	
	///===SETTERS======SETTERS======SETTERS======SETTERS======SETTERS======SETTERS======SETTERS======SETTERS======SETTERS======SETTERS===///




private:

	///===MAIN FUNCTIONS======MAIN FUNCTIONS======MAIN FUNCTIONS======MAIN FUNCTIONS======MAIN FUNCTIONS======MAIN FUNCTIONS======MAIN FUNCTIONS===///

	//set the initial direction bassed on snake input
	void Initial_Direction_Setter_(const sf::Vector2f& new_destination_, const  Direction& new_direction_);

	//transition the snake body to its adjacent segment
	void On_Update_Snake_Body_();

	//transition the snake head to its current direction
	void On_Update_Snake_Head_();

	//if the snake is going back onto itself then reverse its direction
	void Check_Snake_Head_Position_(sf::Vector2f& position_, float& position_to_change_, const float& velocity_, int sign_);

	//check collision and interpolate between points
	void Tick_Snake_Between_Frames_(const std::vector<std::shared_ptr<Snake>>& snakes_);

	//if a snake has been cut its segments are made edable to other snakes
	void Add_Dead_Segments_To_Vector_(std::shared_ptr<SnakeSegment> p);


	///===MAIN FUNCTIONS======MAIN FUNCTIONS======MAIN FUNCTIONS======MAIN FUNCTIONS======MAIN FUNCTIONS======MAIN FUNCTIONS======MAIN FUNCTIONS===///


	///===VARIABLES======VARIABLES======VARIABLES======VARIABLES======VARIABLES======VARIABLES======VARIABLES======VARIABLES======VARIABLES===///

	//the snake sprite used for rendering
	sf::Sprite snake_head_sprite_;
	sf::Sprite snake_body_sprite_;

	//names of textures
	std::string snake_head_texture_name;
	std::string snake_body_texture_name;

	//grid bounds
	const sf::Vector2f& top_left_grid_point_;
	const sf::Vector2f& bottom_right_grid_point_;

	//snake data

	//direction of snake
	Direction direction_{ Direction::eNone };

	//direction previouslty set
	Direction prev_direction_{ Direction::eNone };

	//flag for snake dead
	bool snake_dead_{ false };

	//flag for direction for snake is set
	bool is_direction_set_{ false };

	//movement of snake
	float movement_steps_{ 40 };

	//score of snake
	int score_{ 0 };

	//the electric field positions
	std::vector<sf::Vector2f> electric_field_;

	//flag for electric state
	bool isElectric_{ false };

	//max time for electric 
	unsigned int max_time_left_for_electric_{ 60 };

	//generate time left for electric 
	unsigned int time_left_for_electric_{ rand() % (max_time_left_for_electric_+1) };
	


	//anim data //linked to timestep 
	float anim_time_ = 0;
	float timestep{1.f/60.f};

	Text snake_name_text;


	///===VARIABLES======VARIABLES======VARIABLES======VARIABLES======VARIABLES======VARIABLES======VARIABLES======VARIABLES======VARIABLES===///


protected:
	//list of snake segments
	DoublyLinkedList list_of_segments;

	//allows direction to allways be chaned and used once snake gets in valid position
	Direction direction_queue = Direction::eNone;
		
};

#endif