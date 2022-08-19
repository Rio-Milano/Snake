//singletons
#include "Window.h"
#define Window  Window::Instance_()

#include "TextureManager.h"
#define TextureManager  TextureManager::Instance_()

#include"SoundManager.h"
#define SoundManager  SoundManager::Instance_()

#include"Two_PlayerSnake.h"
#include"GameScene.h"
#include "Snake.h"
#include"PlayerSnake.h"
#include "Utils.h"
#include<vector>
#include"ConfigureScene.h"

//init static snake ID
int  Snake::global_snake_ID = -1;

//ctor
 Snake::Snake(const sf::Vector2f& top_left_grid_point_, const sf::Vector2f& bottom_right_grid_point_, const std::string& snake_name_) :
	 //init list to set attributes
	top_left_grid_point_(top_left_grid_point_),//set grid boundaries
	bottom_right_grid_point_(bottom_right_grid_point_),
	snake_name_text(snake_name_, sf::Vector2f(), 0, 0, 15u, sf::Color::White)
{

	 //list of head names
	static std::vector<std::string> snake_texture_heads
	{
		"D_Default_Head_Texture",
		"C_Default_Head_Texture",
		"B_Default_Head_Texture",
		"A_Default_Head_Texture",
		"Player_Head_Texture",
		"2Player_Head_Texture"
	};

	//list of body names
	static std::vector<std::string> snake_texture_bodys
	{
		"D_Default_Body_Texture",
		"C_Default_Body_Texture", 
		"B_Default_Body_Texture",
		"A_Default_Body_Texture",
		"Player_Body_Texture",
		"2Player_Body_Texture"

	};

	//if vectors are empty
	if (snake_texture_bodys.empty())
	{
		//replenish vectors
		std::vector<std::string> snake_texture_heads2
		{
			"D_Default_Head_Texture",
			"C_Default_Head_Texture",
			"B_Default_Head_Texture",
			"A_Default_Head_Texture",
			"Player_Head_Texture",
			"2Player_Head_Texture"

		};
		snake_texture_heads.insert(snake_texture_heads.end(), snake_texture_heads2.begin(), snake_texture_heads2.end());

		std::vector<std::string> snake_texture_bodys2
		{
			"D_Default_Body_Texture",
			"C_Default_Body_Texture",
			"B_Default_Body_Texture",
			"A_Default_Body_Texture",
			"Player_Body_Texture",
			"2Player_Body_Texture",

		};
		snake_texture_bodys.insert(snake_texture_bodys.end(), snake_texture_bodys2.begin(), snake_texture_bodys2.end());
	}

	//set snake head and body texture
	this->snake_body_texture_name = snake_texture_bodys[snake_texture_bodys.size()-1];
	snake_texture_bodys.size() > 0 ? snake_texture_bodys.pop_back() : void();

	this->snake_head_texture_name = snake_texture_heads[snake_texture_heads.size()-1];
	snake_texture_heads.size() > 0 ? snake_texture_heads.pop_back() : void();

	//if the snake has no ID
	if (this->snake_ID == -1)
	{
		//set snake ID
		snake_ID = ++global_snake_ID;
	}

	
};


//update the snake
void  Snake::Update_(const std::vector<std::shared_ptr<Snake>>& snakes_,  std::vector< std::shared_ptr<Collectable>>& collectables_)
{
	//if the snake is not dead
	if (!snake_dead_)
	{
		//get input for the snake
		Class_Input_(collectables_);

		//if the player enabled player 2 snake
		if(ConfigureScene::P2_On_ == true)
		{
			//this exclusive block of code ensures the seccond player will move when P1 starts moving
			
			//if player 1 snake is moving
			if (snakes_[0]->Get_Has_Snake_Started_Moving())
			{
					//get p2 direction
					switch (snakes_[1]->Get_Direction())
					{
						//if direction is non
						case Direction::eNone:

							//decode direction p2 snake is facing and make direction that direction
							if (snakes_[1]->list_of_segments.Get_Head_()->Get_Pos_().y < list_of_segments.Get_Head_()->Get_Next_()->Get_Pos_().y)
								snakes_[1]->Change_Direction_( Direction::eUp);

							else if (list_of_segments.Get_Head_()->Get_Pos_().y > list_of_segments.Get_Head_()->Get_Next_()->Get_Pos_().y)
								snakes_[1]->Change_Direction_( Direction::eDown);

							else if (list_of_segments.Get_Head_()->Get_Pos_().x < list_of_segments.Get_Head_()->Get_Next_()->Get_Pos_().x)
								snakes_[1]->Change_Direction_( Direction::eLeft);

							else if (list_of_segments.Get_Head_()->Get_Pos_().x > list_of_segments.Get_Head_()->Get_Next_()->Get_Pos_().x)
								snakes_[1]->Change_Direction_( Direction::eRight);

					}
			}

		}

		//if direction is set
		if (is_direction_set_)
		{
			//if the head position is at the head destination
			if (list_of_segments.Get_Head_()->Get_Pos_() == list_of_segments.Get_Head_()->Get_Dest_())
			{
				//set the previous drection to the current direction
				prev_direction_ = direction_;

				//set the direction to the direction in the queue
				direction_ = direction_queue;

				//reset the animation state
				anim_time_ = 0;

				//update the body of the snake
				On_Update_Snake_Body_();
				
				//update the head of the snake
				On_Update_Snake_Head_();

				//get the y and x grid notation of the head destination 
				int snake_x_not_ = int(list_of_segments.Get_Head_()->Get_Dest_().x / 40) - 11;
				int snake_y_not_ = int(list_of_segments.Get_Head_()->Get_Dest_().y / 40) - 1;
				
				//use that x and y notation to add an obsticle to the grid so other snakes can go on that position
				Get_Pathfinding_Instance_().m_grid.Add_Single_Obsticle_(snake_y_not_, snake_x_not_);
			}

			//check collision and interpolate movement
			Tick_Snake_Between_Frames_(snakes_);
		}
	}
}

//draw snake to window
void  Snake::Render_()
{
	//if sprite color is not translucent 
	if (snake_head_sprite_.getColor().a > 0)
	{
		//get the first body segment 
		 std::shared_ptr<SnakeSegment> temp_ = list_of_segments.Get_Head_()->Get_Next_();
		
		//set body texture to the this snakes body texture
		snake_body_sprite_.setTexture(TextureManager.Get_Texture_(snake_body_texture_name));

		//while not gone through all segments 
		while (temp_ != nullptr)
		{
			//set position of sprite to segment position
			snake_body_sprite_.setPosition(sf::Vector2f(temp_->Get_Pos_()));
			
			//draw the body segment 
			Window.Render_Window_Entity_(snake_body_sprite_);
			
			//go to the next segment
			temp_ = temp_->Get_Next_();//move to next segment
		}


		//set the sprite head texture to this snakes head texture name
		snake_head_sprite_.setTexture(TextureManager.Get_Texture_(snake_head_texture_name));
		
		//set temp to the head of the snake
		temp_ = list_of_segments.Get_Head_();//get the head

		//set the origin of the head so it can be rotated about its origin
		snake_head_sprite_.setOrigin(20, 20);
		
		//put direction in switch
		switch (direction_)
		{
		//if direction is none then set the direction to the direction the snake is facing 
		case  Direction::eNone:
			if (list_of_segments.Get_Head_()->Get_Pos_().y < list_of_segments.Get_Head_()->Get_Next_()->Get_Pos_().y)
				direction_ =  Direction::eUp;
			else if (list_of_segments.Get_Head_()->Get_Pos_().y > list_of_segments.Get_Head_()->Get_Next_()->Get_Pos_().y)
				direction_ =  Direction::eDown;
			else if (list_of_segments.Get_Head_()->Get_Pos_().x < list_of_segments.Get_Head_()->Get_Next_()->Get_Pos_().x)
				direction_ =  Direction::eLeft;
			else if (list_of_segments.Get_Head_()->Get_Pos_().x > list_of_segments.Get_Head_()->Get_Next_()->Get_Pos_().x)
				direction_ =  Direction::eRight;

		//up sets rotation to 0 deg
		case  Direction::eUp:
			snake_head_sprite_.setRotation(0);
			break;
		//down sets rotation to 180 deg
		case  Direction::eDown:
			snake_head_sprite_.setRotation(180);
			break;
		//right sets rotation to 90 deg
		case  Direction::eRight:
			snake_head_sprite_.setRotation(90);
			break;
		//left sets rotation to 270 deg
		case  Direction::eLeft:
			snake_head_sprite_.setRotation(270);
			break;
		}
		
		//set position of the snake head
		snake_head_sprite_.setPosition(temp_->Get_Pos_().x + 20, temp_->Get_Pos_().y + 20);
		
		//draw snake head
		Window.Render_Window_Entity_(snake_head_sprite_);//render the head

		//draw snake name tags
		Draw_Tags_();

		//if snake is dead
		if (snake_dead_)
		{
			//set the body sprite color with reduced opacity
			snake_body_sprite_.setColor
			(
				sf::Color(
					snake_body_sprite_.getColor().r,
					snake_body_sprite_.getColor().g, 
					snake_body_sprite_.getColor().b,
					snake_body_sprite_.getColor().a -5
						)
			);

			//set the head sprite color with reduced opacity 
			snake_head_sprite_.setColor
			(
				sf::Color(
					snake_head_sprite_.getColor().r,
					snake_head_sprite_.getColor().g,
					snake_head_sprite_.getColor().b,
					snake_head_sprite_.getColor().a - 5
				)
			);

			//set the id tag color with reduced opacity 
			snake_name_text.Set_Text_Color_(sf::Color(
			snake_name_text.Get_Text_Color_().r,
			snake_name_text.Get_Text_Color_().g,
			snake_name_text.Get_Text_Color_().b,
			snake_name_text.Get_Text_Color_().a-5

			));
		}
	}
}



//make feild
void  Snake::Set_Electric_Field_()
{
	//clear the electric field
	electric_field_.clear();

	//get the head of the snake
	std::shared_ptr<SnakeSegment> seg_ = list_of_segments.Get_Head_();

	//loop through all segments of the snake
	while (seg_ != nullptr)
	{
		//loop around a 3x3 space arround the current segment 
		for (int y = -1; y <= 1; y++)
		{
			for (int x = -1; x <= 1; x++)
			{
				//if at center then ignore 
				if (y == 0 && x == 0)
					continue;

				//get the adjusted position for x and y
				float newX = seg_->Get_Pos_().x + (x * movement_steps_);
				float newY = seg_->Get_Pos_().y + (y * movement_steps_);

				//if adjusted position is out of range of the window bounds then ignore
				if (newX < top_left_grid_point_.x || newX >= bottom_right_grid_point_.x ||
					newY < top_left_grid_point_.y || newY >= bottom_right_grid_point_.y)
					continue;

				//add the electric position to the electric field 
				electric_field_.emplace_back(sf::Vector2f(newX, newY));


			};
		}
		//move to the next segment 
		seg_ = seg_->Get_Next_();
	}
	
}

//draw the electric field to the window
void  Snake::Draw_Electric_Field_(const sf::Color& color_)
{
	//make a rectangle shape for the electric field segments 
	sf::RectangleShape temp_rect_({ movement_steps_, movement_steps_ });
	
	//set color of shape
	temp_rect_.setFillColor(color_);
	
	//loop through all electric field positions
	for (const auto& pos_: electric_field_)
	{
		//set the shape pos to the electric field position 
		temp_rect_.setPosition(pos_);

		//draw the electric field segment 
		Window.Render_Window_Entity_(temp_rect_);
	}
}

//update electric status 
void  Snake::Update_Electric_Field_()
{
	//get the electric field 
	Set_Electric_Field_();

	//if snake is electric 
	if (isElectric_)
		//draw a blue field
		Draw_Electric_Field_(sf::Color(0, 0, 255, 15));
	else
		//if the snake is not electric 

		//draw a white field 
		Draw_Electric_Field_();
}


//extend the snake by n
void  Snake::Extend_Snake_(int n)
{
	//while not added all n segments 
	while(n-- >0)
		//add segment 
		list_of_segments.Add_Segment_();
}


bool Snake::Check_Collision_(const sf::Vector2f& pos_)//take in a point
{
	std::shared_ptr<SnakeSegment> temp_ = list_of_segments.Get_Head_();//get the head of the snake
	while (temp_ != nullptr)//while not checked all segments
	{
		if (temp_->Get_Orig_() == pos_)//if pos colliding with segment
			return true;//return collision has happened
			
		temp_ = temp_->Get_Next_();//otherwise check next segment
	}
	return false;//collision has not happened 
}

//utility functions
void  Snake::Reset_Snake_()
{
	//reset all the snake data for when the snake is reloaded in the run time
	score_ = 0;
	snake_dead_ = false;
	direction_ = Direction::eNone;
	prev_direction_ = Direction::eNone;
	direction_queue = Direction::eNone;
	anim_time_ = 0;
	is_direction_set_ = false;
	list_of_segments.~DoublyLinkedList();
}

void  Snake::AddObsticles()
{
		//define notations for x and y
		int snake_x_not_;
		int snake_y_not_;

		//get the head segment
		std::shared_ptr<SnakeSegment> temp_ = list_of_segments.Get_Head_();

		//while not checked all segments 
		while (temp_ != nullptr)
		{
			//get the grid x and y positions 
			snake_x_not_ = int(temp_->Get_Dest_().x / 40) - 11;
			snake_y_not_ = int(temp_->Get_Dest_().y / 40) - 1;

			//add an obsticle at pos x and y
			Get_Pathfinding_Instance_().m_grid.grid[snake_y_not_][snake_x_not_].m_obsticle = true;

			//go to next segment 
			temp_ = temp_->Get_Next_();
		}
}


void  Snake::On_Update_Snake_Head_()
{
	sf::Vector2f snake_head_dest = { list_of_segments.Get_Head_()->Get_Dest_() };//get head destination

	switch (direction_)
	{
	case Direction::eUp:
		list_of_segments.Get_Head_()->Set_Orig_(list_of_segments.Get_Head_()->Get_Dest_());//get current destination
		Check_Snake_Head_Position_(snake_head_dest, snake_head_dest.y, movement_steps_, -1);//apply method to destination and update it
		break;//same for all other directions

	case Direction::eRight:
		list_of_segments.Get_Head_()->Set_Orig_(list_of_segments.Get_Head_()->Get_Dest_());
		Check_Snake_Head_Position_(snake_head_dest, snake_head_dest.x, movement_steps_, 1);
		break;

	case Direction::eDown:
		list_of_segments.Get_Head_()->Set_Orig_(list_of_segments.Get_Head_()->Get_Dest_());
		Check_Snake_Head_Position_(snake_head_dest, snake_head_dest.y, movement_steps_, 1);
		break;

	case Direction::eLeft:
		list_of_segments.Get_Head_()->Set_Orig_(list_of_segments.Get_Head_()->Get_Dest_());
		Check_Snake_Head_Position_(snake_head_dest, snake_head_dest.x, movement_steps_, -1);
		break;
	}
}

//check for valid data with movement 
void  Snake::Check_Snake_Head_Position_(sf::Vector2f& position_, float& position_to_change_, const float& velocity, int sign_)
{
	//apply change to position vector using direction and velocity
	position_to_change_ += velocity * sign_;

	//if snake destination going into itself then continue going the current direction
	if (list_of_segments.Get_Head_()->Get_Next_()->Get_Pos_() == position_)
	{
		sign_ = -sign_;//invert the velocity coefficient 
		position_to_change_ += 2 * movement_steps_ * sign_;//rectify the position
		list_of_segments.Get_Head_()->Set_Dest_(position_);//set the new destination
		direction_ = prev_direction_;//revert to prev direction
	}
	else
		//set the new destination
		list_of_segments.Get_Head_()->Set_Dest_(position_);//set new direction
}


void  Snake::On_Update_Snake_Body_()
{
	//MORE EFFICIENT METHOD BUT GIVES BAD VISUAL EFFECT//
	
	//list_of_segments.Shift_Tail_Left_();

	// SnakeSegment* temp_ = new  SnakeSegment({}, {}, {});

	// SnakeSegment* head = list_of_segments.Get_Head_();

	//list_of_segments.Add_After_Node_N_(head, temp_);

	//temp_->Set_Orig_(head->Get_Orig_());//set the origin of the snake segment to the destination of the snake segment

	//temp_->Set_Pos_(head->Get_Orig_());

	//temp_->Set_Dest_(head->Get_Dest_());//set the destination of the snake segment to the desination of the next segment



	 std::shared_ptr<SnakeSegment> temp_ = list_of_segments.Get_Tail_();//get the snake tail

	while(temp_->Get_Prev_() != nullptr)//while not reached head
	{
		temp_->Set_Orig_(temp_->Get_Dest_());//set the origin of the snake segment to the destination of the snake segment
		
		temp_->Set_Dest_(temp_->Get_Prev_()->Get_Dest_());//set the destination of the snake segment to the desination of the next segment
		
		temp_ = temp_->Get_Prev_();//update next segment
	}
}
void  Snake::Tick_Snake_Between_Frames_(const std::vector<std::shared_ptr<Snake>>& snakes_)
{

	//if a snake direction has been set
	if (direction_queue != Direction::eNone)
	{
	
		//check if the snake is colliding with a wall
		if (Get_Snake_Pos_().x < top_left_grid_point_.x /*Left wall*/ || Get_Snake_Pos_().x + movement_steps_ > bottom_right_grid_point_.x /*Right wall*/ ||
			Get_Snake_Pos_().y < top_left_grid_point_.y /*top wall*/ || Get_Snake_Pos_().y + movement_steps_ > bottom_right_grid_point_.y /*bottom wall*/)
		{
			//all all snake segments of the snake to the list of dead segments 
			Add_Dead_Segments_To_Vector_(this->list_of_segments.Get_Head_());
			
			//kill the snake
			this->snake_dead_ = true;
			
			//return so no more collision is checked
			return;
		}

		//if snake head has collided with its own body
		if (Check_Collision_(list_of_segments.Get_Head_()->Get_Dest_()))//takes in where the head is going and compares that to all body segments
																		//if body segment position matches destination of snake then collision with self is true
		{
			//add all the snake segments to the list of dead segments
			Add_Dead_Segments_To_Vector_(this->list_of_segments.Get_Head_());
			//kill the snake
			this->snake_dead_ = true;
			//return so no more collision is checked
			return;
		}


		/*check collision with other snakes*/

		//loop through all snakes
		for (auto& snake_ : snakes_)
		{
			if (this != snake_.get())
			{
				//if the other snake is alive
				if (snake_->Get_Is_Snake_Alive_())
				{
				//if we are not checking collision with self
					//make a temp pointer for a snake segment
					 std::shared_ptr<SnakeSegment> head_ = nullptr;

					//if the snake is in its electric state
					if (snake_->Get_Is_Snake_Electric())
					{
						//set the segment pointer = to the head of the *this snake
						head_ = this->list_of_segments.Get_Head_();

						//create a variable to count segments (used so if electric field is colliding with the first 3 segments then we kill *this snake )
						int segment_number_ = 1;

						//loop through all the segments of this snake
						while (head_ != nullptr)
						{
							//loop through all the electric field positions of the other snake
							for (const auto& field_pos_ : snake_->Get_Electric_Field_())
							{
								
								//if the segment and the electric field position are colliding
								if(sqrt(pow(head_->Get_Pos_().x - field_pos_.x, 2) + pow(head_->Get_Pos_().y - field_pos_.y, 2)) < movement_steps_)
								{
									//if the segment is in the first 3 segments of the snake
									if(segment_number_ <= 3)
									{
										//add all of *this snakes segments to the list of dead segments 
										Add_Dead_Segments_To_Vector_(this->list_of_segments.Get_Head_());
										//kill *this snake
										this->snake_dead_ = true;

										//increase the score of the other snake for killing *this snake
										snake_->Set_Increase_Snake_Score_(1);

										//cast the other snake to a player snake
										PlayerSnake* player_snake_ = dynamic_cast<PlayerSnake*> (snake_.get());

										//if cast successful then play killing snkae sound
										if (player_snake_)
											SoundManager.Play_Sound_("Killed_Snake_Sound");

										//add text notification to the screen
										 GameScene::text_notifi_.push_back(Text("+" + std::to_string(1), snake_->Get_Snake_Dest_()));

										//return as *this snake has been killed
										return;
									}
									//if the collision between the electric field and *this segment is not between (1 <= x <= 3) then simply remove all the segments after and including that segment 
									else
									{
										//add all relevent segments of *this snake to the dead snake vector  
										Add_Dead_Segments_To_Vector_(head_);

										//remove all the relevent snake segments from *this snake
										this->Remove_Segments_(head_);

										//increase the other snakes score as they have damaged *this snake;
										snake_->Set_Increase_Snake_Score_(1);

										//add text notification to the screen
										 GameScene::text_notifi_.push_back(Text("+" + std::to_string(1), snake_->Get_Snake_Dest_()));
										
										//return as collision is finished
										return;
									}
									
								}
					
							}
							//move onto the next segment
							head_ = head_->Get_Next_();

							//increment the segment number;
							segment_number_+=1;
						}
					}
					//if the snake is not electric
					else {
						//set the segment pointer = to the head of the other snake
						head_ = snake_->Get_Snake_Head_();

						/*check to see if there is a head on head collision between *this snake and other snake*/


						if (this->Get_Snake_Head_()->Get_Dest_() == head_->Get_Dest_())
						{
							//add all segments of both colliding snakes to the dead snakes vector
							this->Add_Dead_Segments_To_Vector_(this->list_of_segments.Get_Head_());
							snake_->Add_Dead_Segments_To_Vector_(snake_->Get_Snake_Head_());
							
							//kill both the snakes
							this->snake_dead_ = true;
							snake_->Set_Is_Snake_Dead_(true);
							return;
						}

						/*check if *this snake is colliding with any other body segment of the other snake*/
						
						//move onto the next segment of the other snake
						head_ = head_->Get_Next_();

						//loop through all the segments of the other snake
						while (head_ != nullptr)
						{
							//if the destination of *this snake head is == to a segment on other snake then
							
							if (this->Get_Snake_Head_()->Get_Dest_() == head_->Get_Pos_())
							{
								//add all segments of *this snake to dead snake vector
								this->Add_Dead_Segments_To_Vector_(this->list_of_segments.Get_Head_());
								
								//kill the snake
								this->snake_dead_ = true;
								
								//return so no more collision is checked
								return;
							}
							//move onto next segment
							head_ = head_->Get_Next_();

						}
					}
					
					

					
				}
			}

			//loop through all segments of dead snake segments 
			for (std::list<sf::Vector2f>::iterator i = GameScene::dead_segments_.begin(); i != GameScene::dead_segments_.end(); i++)
			{
				//get the destination of this snake
				sf::Vector2f this_snake_dest_ = this->Get_Snake_Head_()->Get_Dest_();
				
				//if the head of this snake has collided with the dead segment 
				if (sqrt(pow(this_snake_dest_.x - i->x, 2) + pow(this_snake_dest_.y - i->y, 2)) < movement_steps_ - 10.f)
				{
					//remove the dead snake segment from the list
					GameScene::dead_segments_.erase(i);

					//increase the snake score of this snake
					Set_Increase_Snake_Score_(1);

					//cast this snake to a player
					PlayerSnake* player_snake_ = dynamic_cast<PlayerSnake*> (this);

					//if cast is successful 
					if (player_snake_)
						//play food collection sound 
						SoundManager.Play_Sound_("FoodCollection");

					//make the snake bigger
					Extend_Snake_(1);

					//text object with score is created
					GameScene::text_notifi_.push_back(Text("+" + std::to_string(1), Get_Snake_Dest_()));

					//if there no segments left in the list
					if (GameScene::dead_segments_.size() == 0)
						break;//no more check for collision

					//update the head of the list
					i = GameScene::dead_segments_.begin();
				}
			}
		}
		//interpolate the snake movement 
		Move_Snake_();
	}

}

//add segments from cutoff to dead segments list
void  Snake::Add_Dead_Segments_To_Vector_(std::shared_ptr<SnakeSegment> p)
{
	//while not at end of snake
	while (p != nullptr)
	{
		//add the position of the segment to the list of dead segments 
		GameScene::dead_segments_.emplace_back(p->Get_Pos_());

		//move to the next segment 
		p = p->Get_Next_();
	}
}


//interpolate snake movement 
void  Snake::Move_Snake_()
{
	//increment time passed 
	anim_time_ += timestep;
	
	//find unit coefficient 
	float f = std::min(anim_time_/6 * movement_steps_, 1.f);//find interpolation factor 0->1

	//get the tail of the snake
	std::shared_ptr<SnakeSegment> temp_ = list_of_segments.Get_Tail_();//get current tail
	
	
	while (temp_ != nullptr)//while not updated all segments
	{
		//get orig and dest points 
		sf::Vector2f snake_seg_orig_{ temp_->Get_Orig_() };
		sf::Vector2f snake_seg_dest_{ temp_->Get_Dest_() };

		//define a new point for the snake segment 
		sf::Vector2f snake_seg_new_pos_;
		
		//interpolate between orig and dest
		snake_seg_new_pos_.x = lerp(snake_seg_orig_.x, snake_seg_dest_.x, f);
		snake_seg_new_pos_.y = lerp(snake_seg_orig_.y, snake_seg_dest_.y, f);

		//set the position to the new segment
		temp_->Set_Pos_(snake_seg_new_pos_);

		//move back up the list of segments 
		temp_ = temp_->Get_Prev_();
	}
}



//update the electric timers 
void  Snake::Update_Electric_()
{
	//if the snake is electric 
	if (isElectric_)
	{
		//if the time is over for electric state 
		if (time_left_for_electric_ == 0)
		{
			//turn off electric state
			isElectric_ = false;

			//reset time left for electric for next time electric state is enabled 
			time_left_for_electric_ = rand() % (max_time_left_for_electric_ + 1);
		}
		//if still time left for electric state to be over
		else
			//reduce time left for electric state
			time_left_for_electric_--;
	}
}

//remove segments after segment 
int  Snake::Remove_Segments_( std::shared_ptr<SnakeSegment> remove_segment_)
{
	//get the tail of the snake to the previous of the segmenet passed 
	this->list_of_segments.Set_Tail_(remove_segment_->Get_Prev_());

	//the previous of the segments passed next pointer is null
	remove_segment_->Get_Prev_()->Set_Next_(nullptr);

	//amount of segments removed
	int amount_of_segments_removed_ = 0;

	//while not at end of list of segments 
	while (1)
	{
		//if the next pointer is null
		if (remove_segment_->Get_Next_() == nullptr) 
		{
			//return the amount of segments removed + 1
			return ++amount_of_segments_removed_;
		}
		else
		{
			//segment = next of segment 
			remove_segment_ = remove_segment_->Get_Next_();
			
			//increment segment 
			amount_of_segments_removed_++; 
		}
	}
}

//draw ID tags 
void  Snake::Draw_Tags_()
{
	//set the snake ID position to the snake head position 
	snake_name_text.Set_Position_(list_of_segments.Get_Head_()->Get_Pos_());

	//draw the snake ID to the window 
	snake_name_text.Render_();
}

//the function will aid the initial setting of the snake when the game is first displayed 
void  Snake::Initial_Direction_Setter_(const sf::Vector2f& new_destination_, const  Direction& new_direction_)
{
	//set the head destination to the new destination 
	list_of_segments.Get_Head_()->Set_Dest_(new_destination_);

	//direction is set is true
	is_direction_set_ = true;

	//set the directions of the snake
	this->direction_queue = new_direction_;
	this->prev_direction_ = new_direction_;
	this->direction_ = new_direction_;	
}

//change the direction of the snake 
void  Snake::Change_Direction_(const Direction& direction__)
{
	//if the direction is set
	if (is_direction_set_)
		//set the direction to the direction queue
		direction_queue = direction__;

	//if the direction is not set
	else
	{
		//get the destination of the head 
		sf::Vector2f current_dest_ = list_of_segments.Get_Head_()->Get_Pos_();

		//put passed direction in a switch 
		switch (direction__)
		{
		/*
		
		decode each direction and pass the new destination and the new direction which will be used to inti the snake first movement 
		
		*/

		case Direction::eUp:
			if (current_dest_.y <= list_of_segments.Get_Head_()->Get_Next_()->Get_Pos_().y)
				Initial_Direction_Setter_({current_dest_.x, current_dest_.y - movement_steps_},  Direction::eUp);
			break;

		case Direction::eDown:

			if (current_dest_.y >= list_of_segments.Get_Head_()->Get_Next_()->Get_Pos_().y)
				Initial_Direction_Setter_({ current_dest_.x, current_dest_.y + movement_steps_ },  Direction::eDown);
			break;


		case Direction::eLeft:
			if (current_dest_.x <= list_of_segments.Get_Head_()->Get_Next_()->Get_Pos_().x)
				Initial_Direction_Setter_({ current_dest_.x - movement_steps_, current_dest_.y},  Direction::eLeft);
			break;


		case Direction::eRight:
			if (current_dest_.x >= list_of_segments.Get_Head_()->Get_Next_()->Get_Pos_().x)
				Initial_Direction_Setter_({ current_dest_.x + movement_steps_, current_dest_.y},  Direction::eRight);
			break;
		}
	}
}
