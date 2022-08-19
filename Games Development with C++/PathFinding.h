#ifndef PATHFINDING_H
#define PATHFINDING_H

#include<vector>
#include<utility>

#include"GridNode.h"
#include"Grid.h"

#include"PriorityQueue.h"

/*

this class is solely responsible for finding paths from 1 place in the grid to another 

*/

class PathFinding
{
public:
	//ctors and dtors
	PathFinding() = default;
	~PathFinding() = default;

	//algorithm to prime the grid with data that can be used for path fetching 
	void Run(int startX, int startY, int endX, int endY, const int& snakeID);

	//collect a path from the graph from a given point
	std::vector<std::pair<int, int>> GetPath(int endX, int endY);

	//check if there is a path from a given point
	inline const bool Get_Is_Path_(const int& endY, const int& endX) { return m_grid.grid[endY][endX].m_parent == nullptr ? false : true; };
	
	//the grid object holding the info about nodes
	Grid m_grid;

private:
	//the priority queue used for odering nodes by their F cost or by their H cost
	PriorityQueue m_open_set;
};

#endif