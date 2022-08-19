#include "Grid.h"
#include<iostream>

Grid::Grid()
{
	//loop through each position of grid and set its x and y pos
	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_cols; j++)
		{
			grid[i][j].m_x = j;
			grid[i][j].m_y = i;
		}
	}
}


void Grid::Reset()
{
	//loop through each position of grid and reset their values to their default 
	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_cols; j++)
		{
			grid[i][j].m_g_cost = INF;
			grid[i][j].m_h_cost = INF;
			grid[i][j].m_locked = false;
			grid[i][j].m_discovered = false;
			grid[i][j].m_parent = nullptr;
			grid[i][j].pos_in_PQ = 1;
			grid[i][j].snake_ID = -1;
		}
	}

}

void Grid::ResetObsticles()
{
	//loop through each position of the grid and set their position to their default one 
	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_cols; j++)
		{
			grid[i][j].m_obsticle = false;
			grid[i][j].snake_ID = -1;
		}
	}
}

void Grid::Add_Single_Obsticle_(const int& y, const int& x)
{
	//set a position on the grid to be an obsticle 
	if (x < 0 || x >= m_cols || y < 0 || y >= m_rows)
		return;
	grid[y][x].m_obsticle = true;
}


std::vector<GridNode*> Grid::Get_Adjacent_Vertices_(GridNode*& m_node, const int& snakeID)
{
	//define a vector to hold vertices
	std::vector<GridNode*> adjecent_vertices_;

	//loop through a 3x3 grid arround the vertex
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			//if the vertex is a diagonal then ignore it
			if ((i == 0 && j == 0) || (i == -1 && j == -1) || (i == -1 && j == 1) || (i == 1 && j == -1) || (i == 1 && j == 1))
				continue;
			
			//define the vertex position
			int adj_X = m_node->m_x + j;
			int adj_Y = m_node->m_y + i;

			//if vertex position is out of bounds then ignore it
			if (adj_X < 0 || adj_X >= m_cols || adj_Y < 0 || adj_Y >= m_rows)
				continue;

			//get the adjacent vertex snakeID number
			int snakeID_res_node = grid[adj_Y][adj_X].snake_ID;

			//if vertex has been locked by a snake
			if (snakeID_res_node != -1)
			{
				//if the snake that locked it is not the snake requesting a path
				if (snakeID_res_node != snakeID)
					continue;//ignore the vertex
			}
			//add the vertex to the grid
			adjecent_vertices_.emplace_back(&grid[adj_Y][adj_X]);
		}
	}
	//return the final list of ajacent vertices
	return adjecent_vertices_;

}
