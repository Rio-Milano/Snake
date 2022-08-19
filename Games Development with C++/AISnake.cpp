#include "AISnake.h"
#include "Window.h"
#include<utility>
#define Window  Window::Instance_()


#include<iostream>
void  AISnake::Class_Input_(std::vector<std::shared_ptr<Collectable>>& collectables_)
{
		//randomize the odering of the collectables 
		std::random_shuffle(collectables_.begin(), collectables_.end());//note this will change the actual list as passing by ref

		//get the start x and y positions of the snake
		startX = (int(Get_Snake_Pos_().x) / 40) - 11;
		startY = (int(Get_Snake_Pos_().y) / 40) - 1;

		//define a collection of collectables that are not accessible to the snake
		std::vector<std::shared_ptr<Collectable>> locked_collectables_;

		//while there are collectables to check
		while (locked_collectables_.size() != collectables_.size())
		{
			//if the snake is locked onto a collectable
			if (coll != nullptr)
			{
				//if the collectable is not alive
				if (coll->Get_Is_Alive_() == false)
					//make the snake not locked onto a collectable
					coll = nullptr;
			}

			//if the snake is not locked onto a collectable 
			if (coll == nullptr)
			{
				//loop through all the collectables 
				for (const auto& x : collectables_)
				{
					//if the collectable is alive and the collectable is a food item and the collectable is not in the collection of locked collectables 
					if (x->Get_Is_Alive_() && x->Get_Collectable_Type_() == E_CollectableType::eFood && std::find(locked_collectables_.begin(), locked_collectables_.end(), x) == locked_collectables_.end())
					{
						//set the goal x,y
						goalX = (int(x->Get_Pos_().x) / 40) - 11;
						goalY = (int(x->Get_Pos_().y) / 40) - 1;
						
						//update the collectable the snake is locked on to
						coll = x;

						//break from the searching loop
						break;
					};
				}
			}

			//reset the nodes of the graph
			Get_Pathfinding_Instance_().m_grid.Reset();

			//run pathfinding from the snake position to the collectable 
			Get_Pathfinding_Instance_().Run(startX, startY, goalX, goalY, this->snake_ID);

			//obtain the path from the snake position to the collectable 
			std::vector < std::pair<int, int>> path_ = Get_Pathfinding_Instance_().GetPath(goalX, goalY);

			//if there is a path to thge collectable 
			if (Get_Pathfinding_Instance_().Get_Is_Path_(goalY, goalX))
			{
				//take the closest node to go to

				//if node is above snake then go up
				if (path_[path_.size() - 1].second < startY)
					Change_Direction_( Direction::eUp);

				//if node is to left of snake then go left
				else if (path_[path_.size() - 1].first < startX)
					Change_Direction_( Direction::eLeft);

				//if node is underneath snake then go down
				else if (path_[path_.size() - 1].second > startY)
					Change_Direction_( Direction::eDown);

				//if the node is to the right of the snake then go right
				else if (path_[path_.size() - 1].first > startX)
					Change_Direction_( Direction::eRight);
				
				//exit path finding
				return;
			}
			else //if there is no path to the collectable 
			{
				//add the collectable to the collection of locked collectables
				locked_collectables_.emplace_back(coll);

				//remove the selection of the chosen collectable
				coll = nullptr;

				//decide what direction the snake is facing then go in that direction 
				if (list_of_segments.Get_Head_()->Get_Pos_().y < list_of_segments.Get_Head_()->Get_Next_()->Get_Pos_().y)
					direction_queue =  Direction::eUp;
				else if (list_of_segments.Get_Head_()->Get_Pos_().y > list_of_segments.Get_Head_()->Get_Next_()->Get_Pos_().y)
					direction_queue =  Direction::eDown;
				else if (list_of_segments.Get_Head_()->Get_Pos_().x < list_of_segments.Get_Head_()->Get_Next_()->Get_Pos_().x)
					direction_queue =  Direction::eLeft;
				else if (list_of_segments.Get_Head_()->Get_Pos_().x > list_of_segments.Get_Head_()->Get_Next_()->Get_Pos_().x)
					direction_queue =  Direction::eRight;
			}


		}

	}
