#include "PathFinding.h"

void PathFinding::Run(int startX, int startY, int endX, int endY, const int& snake_ID)
{
	//Clear the open set for the next run of the Alg
	m_open_set.clearHeap();

	//init the start vertex
	m_grid.grid[startY][startX].m_g_cost = 0;


	//add the start vertex onto the open set
	m_open_set.addToHeap(std::make_pair(startY, startX), m_grid.grid);

	//define a current node
	GridNode* current_node_;

	//while the open set has nodes
	while (m_open_set.size() > 0)
	{
		//get the current node
		std::pair<int, int> optimal_node_grid_position_ = m_open_set.deleteMin(m_grid.grid);
		current_node_ = &m_grid.grid[optimal_node_grid_position_.first][optimal_node_grid_position_.second];//m_open_set[0];

		//lock the current node
		current_node_->m_locked = true;

		//if the current node is found then end the alg
		if (current_node_ == &m_grid.grid[endY][endX])
			return;

		//loop through all adjacent nodes
		for (const auto& adj : m_grid.Get_Adjacent_Vertices_(current_node_, snake_ID))
		{
			if (adj->m_obsticle || adj->m_locked)//if node is obsticle or node is locked then dont expand node
				continue;

			//if node is not discovered
			if (adj->m_discovered == false)
			{
				//make discovered
				adj->m_discovered = true;

				//set the h cost
				adj->m_h_cost = static_cast<float>(abs(endY - adj->m_y) + abs(endX - adj->m_x));

				//add node to open set
				m_open_set.addToHeap(std::make_pair(adj->m_y, adj->m_x), m_grid.grid);
			}

			//get distance to adj node
			float adj_cost_ = current_node_->m_g_cost + 1;

			//if current node g cost + adj distance cost is less than the adj g cost
			if (adj_cost_ < adj->m_g_cost)
			{
				//set the g cost
				adj->m_g_cost = adj_cost_;

				//set the parent of adj
				adj->m_parent = current_node_;

				//sift up node as its attributes have been reduced in value
				m_open_set.siftUp(adj->pos_in_PQ, m_grid.grid);
			}
		}


	};
}
std::vector<std::pair<int, int>> PathFinding::GetPath(int endX, int endY)
{
	//define a vector to hold the path
	std::vector<std::pair<int, int>> path_;

	//define the node at the end
	GridNode* pos_ = &m_grid.grid[endY][endX];

	//while the end node has a parent 
	while (pos_->m_parent != nullptr)
	{
		//add the end node onto the vector
		path_.emplace_back(std::make_pair(pos_->m_x, pos_->m_y));

		//update the node to hold its parent
		pos_ = pos_->m_parent;
	}

	//return the collected path
	return path_;
};