#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include<iostream>
#include"GridNode.h"
#include"Grid.h"

/*

this class implements the min heap and is used for an efficient use of A* pathfinding
*/

class PriorityQueue
{

public:
	//ctors and dtors
	PriorityQueue() = default;
	~PriorityQueue() = default;

	/*
	Heapify ops
	*/

	//sift a node up the heap when adding nodes
	void siftUp(const int, GridNode[][Grid::m_cols]);

	//sift a node down the heap when removing nodes
	void Siftdown(int, GridNode [][Grid::m_cols]);

	//add a new node to the heap
	void addToHeap(std::pair<int, int>, GridNode [][Grid::m_cols]);

	//delete the min from the heap
	const std::pair<int, int> deleteMin(GridNode [][Grid::m_cols]);

	//get the min from the heap
	const std::pair<int, int> peakNextMin();

	//remove all nodes from the heap
	void clearHeap();

	//get the size of the heap
	inline const int size() { return nextFreePosInPrioityQueue - 1; }


private:
	//swap the 2 nodes at 2 positions
	void swapNodes(int , int, GridNode[][Grid::m_cols]);

	//get the next free position in the heap
	inline const int& getNextFree() const {
		return nextFreePosInPrioityQueue;
	};

	//the heap
	std::pair<int, int> heap[1000];//giving 1000 elements for the heap
	
	//the size of the heap
	int maxPosInPriorityQueue = 1000;//needed to know when heep is full
	int nextFreePosInPrioityQueue = 1;//heap is 1 bassed
};

#endif
