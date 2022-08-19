#ifndef GRID_H
#define GRID_H

#include"GridNode.h"
#include<vector>
#include<SFML/Graphics.hpp>

/*

This class abstracts the grid in the game to an array of nodes that can be used for pathfinding

*/

class Grid
{
public:
	//ctors and dtors 
	Grid();
	~Grid() {};

	//clears all data in the grid appart from obsticles
	void Reset();

	//reset all obsticles to false
	void ResetObsticles();

	//adds an obsticle to the grid 
	void Add_Single_Obsticle_(const int& y, const int& x);

	//get all the vertices arround a vertex
	std::vector<GridNode*> Get_Adjacent_Vertices_(GridNode*& m_node, const int& snakeID);

	//grid, rows, columns 
	static constexpr int m_rows{ 25 };
	static constexpr int m_cols{ 25 };
	GridNode grid[m_rows][m_cols];

};

#endif