#ifndef GRIDNODE_H
#define GRIDNODE_H

#define INF 10000

/*
this class represents all the individial nodes in the grid that represents the game board for snake game
*/

class GridNode
{
public:

		//gets the combined heuristic costs
		inline const float Get_F_Cost_() const { return (m_g_cost + m_h_cost); };

		//node properties 
		bool	m_obsticle = false,
				m_locked = false,
				m_discovered = false;

		//the heuristic values
		float	m_g_cost = INF,
				m_h_cost = INF;
		
		//the x and y position on the grid
		int		m_x,
				m_y;

		//when running path finding this is used for backtracking 
		GridNode* m_parent = nullptr;

		//position in the heap
		int pos_in_PQ = 1;

		//-1 when no snake is reserving that position
		int snake_ID = -1;

};

#endif
