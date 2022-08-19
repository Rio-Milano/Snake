#include "PriorityQueue.h"

//sift a node up the heap when adding nodes
void PriorityQueue::siftUp(int given_PriorityQueuePosition, GridNode graph[][Grid::m_cols] )
{
	//Calculate where the parent of the given node is
	int parent_ofVertex = int(floor(given_PriorityQueuePosition / 2));

	//While the parent points to a valid node
	while 
	(parent_ofVertex != 0 && 
		
		//the parent of the node has a bigger F cost than the current node
		(
		graph[(heap[parent_ofVertex].first)][heap[parent_ofVertex].second].Get_F_Cost_() >
		graph[heap[given_PriorityQueuePosition].first][heap[given_PriorityQueuePosition].second].Get_F_Cost_()
		//or
		||
		//the F costs are the same but the parents H cost is bigger than the current node
				(

					graph[(heap[parent_ofVertex].first)][heap[parent_ofVertex].second].Get_F_Cost_() ==
					graph[heap[given_PriorityQueuePosition].first][heap[given_PriorityQueuePosition].second].Get_F_Cost_() &&

					graph[(heap[parent_ofVertex].first)][heap[parent_ofVertex].second].m_h_cost > 
					graph[heap[given_PriorityQueuePosition].first][heap[given_PriorityQueuePosition].second].m_h_cost
				)

		)
	)


	{
		//swap the parent and the given node
		swapNodes(parent_ofVertex, given_PriorityQueuePosition, graph);

		//Update new position of given node and calculate new position of parent
		given_PriorityQueuePosition = parent_ofVertex;
		parent_ofVertex = int(floor(given_PriorityQueuePosition / 2));
	}
}

void PriorityQueue::Siftdown(int given_PriorityQueuePosition, GridNode graph[][Grid::m_cols])
{
	//positions of nodes needed to use
	int leftChildPos;
	int rightChildPos;
	int currentNodePos;


	//While the node is not in the correct position in heap
	while (1)
	{
		leftChildPos = given_PriorityQueuePosition * 2;//get children positions
		rightChildPos = given_PriorityQueuePosition * 2 + 1;
		currentNodePos = given_PriorityQueuePosition;//get the current node position
		
		//If the node has no childen then it is in the correct place
		if (leftChildPos >= nextFreePosInPrioityQueue && rightChildPos >= nextFreePosInPrioityQueue)
			return;

		//If the node only has 1 left child
		else if (rightChildPos >= nextFreePosInPrioityQueue)
		{
			//Check if that left child is smaller in priority than the current node, if so swap it
			if (graph[heap[leftChildPos].first][heap[leftChildPos].second].Get_F_Cost_() < graph[heap[currentNodePos].first][heap[currentNodePos].second].Get_F_Cost_()
				||//OR
				(
					//the left child has the same priority as the current node but the left child has a lower H cost than the current node
					graph[(heap[leftChildPos].first)][heap[leftChildPos].second].Get_F_Cost_() ==
					graph[heap[currentNodePos].first][heap[currentNodePos].second].Get_F_Cost_() &&

					graph[(heap[leftChildPos].first)][heap[leftChildPos].second].m_h_cost <
					graph[heap[currentNodePos].first][heap[currentNodePos].second].m_h_cost
					))
			{
				//swap the nodes
				swapNodes(graph[heap[leftChildPos].first][heap[leftChildPos].second].pos_in_PQ, given_PriorityQueuePosition, graph);//swap the left child and the given node

				//update the current node position
				given_PriorityQueuePosition = graph[heap[leftChildPos].first][heap[leftChildPos].second].pos_in_PQ;
			}

			else   //If the left node was not smaller then return as node is in correct place
				return;
		}

		//if the node has 2 children then check if either one of them is smaller than the current node
		else
		{
			if (graph[heap[currentNodePos].first][heap[currentNodePos].second].Get_F_Cost_() > graph[heap[leftChildPos].first][heap[leftChildPos].second].Get_F_Cost_() ||
				graph[heap[currentNodePos].first][heap[currentNodePos].second].Get_F_Cost_() > graph[heap[rightChildPos].first][heap[rightChildPos].second].Get_F_Cost_())
			{
				//if the left child is smaller
				if (graph[heap[leftChildPos].first][heap[leftChildPos].second].Get_F_Cost_() <
					graph[heap[rightChildPos].first][heap[rightChildPos].second].Get_F_Cost_())
				{
				
					//swap the left child with the given node
					swapNodes(graph[heap[leftChildPos].first][heap[leftChildPos].second].pos_in_PQ, given_PriorityQueuePosition, graph);

					//Update new positions in priority queue
					given_PriorityQueuePosition = graph[heap[leftChildPos].first][heap[leftChildPos].second].pos_in_PQ;
				}
				else {
					//Swap current node with the right child
					swapNodes(graph[heap[rightChildPos].first][heap[rightChildPos].second].pos_in_PQ, given_PriorityQueuePosition, graph);

					//Update new positions in priority queue
					given_PriorityQueuePosition = graph[heap[rightChildPos].first][heap[rightChildPos].second].pos_in_PQ;

				}
			}
			else//we cant make a swap bassed on F cost as they either both the same and OR == to the F cost of the current node
			{
				//if the node's F cost is smaller than both the left and right child then the node is in the correct place
				if (graph[heap[currentNodePos].first][heap[currentNodePos].second].Get_F_Cost_() < graph[(heap[leftChildPos].first)][heap[leftChildPos].second].Get_F_Cost_() &&
					graph[heap[currentNodePos].first][heap[currentNodePos].second].Get_F_Cost_() < graph[(heap[rightChildPos].first)][heap[rightChildPos].second].Get_F_Cost_())
					return;

				//the nodes F cost is the same as the f cost of the left and right child so use H cost

				if (graph[(heap[leftChildPos].first)][heap[leftChildPos].second].m_h_cost < graph[heap[currentNodePos].first][heap[currentNodePos].second].m_h_cost ||
					graph[(heap[rightChildPos].first)][heap[rightChildPos].second].m_h_cost < graph[heap[currentNodePos].first][heap[currentNodePos].second].m_h_cost)
				{
					//if the left node H cost is smaller then right node H cost
					if (graph[(heap[leftChildPos].first)][heap[leftChildPos].second].m_h_cost < graph[(heap[rightChildPos].first)][heap[rightChildPos].second].m_h_cost)
					{
						//swap with left child
						swapNodes(graph[heap[leftChildPos].first][heap[leftChildPos].second].pos_in_PQ, given_PriorityQueuePosition, graph);

						//Update new positions in priority queue
						given_PriorityQueuePosition = graph[heap[leftChildPos].first][heap[leftChildPos].second].pos_in_PQ;
					}
					//else swap with right
					else if (graph[(heap[leftChildPos].first)][heap[leftChildPos].second].m_h_cost > graph[(heap[rightChildPos].first)][heap[rightChildPos].second].m_h_cost)
					{
						//Swap current node with the right child
						swapNodes(graph[heap[rightChildPos].first][heap[rightChildPos].second].pos_in_PQ, given_PriorityQueuePosition, graph);

						//Update new positions in priority queue
						given_PriorityQueuePosition = graph[heap[rightChildPos].first][heap[rightChildPos].second].pos_in_PQ;
					}
					else
						return;

				}
				else return;

			}
		}
	}
}

void PriorityQueue::addToHeap(std::pair<int, int> given_priority, GridNode graph[][Grid::m_cols])
{
	//if the heap is full
	if (nextFreePosInPrioityQueue == maxPosInPriorityQueue)
		std::cout << "Error: Heap is full" << std::endl;//report error
	else
	{
		//Add the entry into the next free position in the heap
		heap[nextFreePosInPrioityQueue] = given_priority;

		//set the new node pos in PQ
		graph[given_priority.first][given_priority.second].pos_in_PQ = nextFreePosInPrioityQueue;
		
		//increment next avaliable space
		nextFreePosInPrioityQueue++;

		//Heapify the node
		siftUp(nextFreePosInPrioityQueue - 1, graph);
	}
}

const std::pair<int, int> PriorityQueue::deleteMin(GridNode graph[][Grid::m_cols])
{
	//if the heap is empty
	if (nextFreePosInPrioityQueue == 1)
	{
		//report error
		std::cout << "Error: Heap is empty" << std::endl;
		return{ -1, -1 };
	}
	else
	{
		//if heap is not empty
		std::pair<int, int> temp = heap[1];//Take the node from the top
		
		//place the end node at the start of heap
		heap[1] = heap[nextFreePosInPrioityQueue - 1];//set root node = to farthest node

		//set the new start node pos in PQ to 1
		graph[heap[1].first][heap[1].second].pos_in_PQ = 1;//update the nodes position in the priority queue

		//decrement the next free in PQ
		nextFreePosInPrioityQueue--;//make farthest most node as an avaliable spot

		//If there is still nodes in the Priority Queue then heapify the current node
		if (nextFreePosInPrioityQueue != 1)
			Siftdown(1, graph);

		//Return the min node
		return temp;
	}
};


const std::pair<int, int> PriorityQueue::peakNextMin()
{
	//if the heap is empty
	if (nextFreePosInPrioityQueue == 1)
	{
		//report error
		std::cout << "Error: Heap is empty" << std::endl;
		return { -1, -1 };
	}
	//if the heap is not empty then return the top of the heap
	return { heap[1].first, heap[1].second };
}

void PriorityQueue::swapNodes(int given_PriorityQueuePosition_A, int given_PriorityQueuePosition_B,  GridNode graph[][Grid::m_cols])//helper function for sift up and down. Used to avoid redundant code when needing swapping
{
	//Swap the Vertices at the 2 given positions
	std::pair<int, int> temp = heap[given_PriorityQueuePosition_A];
	heap[given_PriorityQueuePosition_A] = heap[given_PriorityQueuePosition_B];
	heap[given_PriorityQueuePosition_B] = temp;

	//Update positions of the swapped vertices in priority queue
	graph[heap[given_PriorityQueuePosition_B].first][heap[given_PriorityQueuePosition_B].second].pos_in_PQ = given_PriorityQueuePosition_B; //>posInPQ = given_PriorityQueuePosition_B;
	graph[heap[given_PriorityQueuePosition_A].first][heap[given_PriorityQueuePosition_A].second].pos_in_PQ = given_PriorityQueuePosition_A; //>posInPQ = given_PriorityQueuePosition_B;
}

void PriorityQueue::clearHeap()
{
	//set the next free to the first pos in the heap
	nextFreePosInPrioityQueue = 1;
}