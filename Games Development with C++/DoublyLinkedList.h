#ifndef LINKEDLIST_H
#define LINKEDLIST_H


#include <SFML/Graphics.hpp>
#include "SnakeSegment.h"


class DoublyLinkedList
{
public:

	//Ctors and Dtors
	DoublyLinkedList() = default;
	~DoublyLinkedList() = default;

	/*
	Utility Functions
	*/
	
	//

	//used for creating the snake
	void Add_Segment_At_Point_(const sf::Vector2f& pos_, const sf::Vector2f& orig_, const sf::Vector2f& dest_);
	
	//used for extending the snake
	void Add_Segment_();


	/*
	Getters
	*/

	//get the last segment in the list
	inline  const std::shared_ptr<SnakeSegment> Get_Tail_() const{ return this->m_tail; };

	//get the first segment in the list
	inline  const std::shared_ptr<SnakeSegment> Get_Head_() const { return this->m_head; };
	
	//used for more efficient snake movement method
	// inline void Shift_Tail_Left_() { m_tail = m_tail->Get_Prev_();  m_tail->Set_Next_(nullptr); };
	
	//used to add a segment after another segment
	void Add_After_Node_N_(const std::shared_ptr<SnakeSegment>& N, const std::shared_ptr<SnakeSegment>& new_N);

	//set the tail of list to a new segment 
	inline void Set_Tail_( std::shared_ptr<SnakeSegment> new_tail) { this->m_tail = new_tail; }

private:
	//head a tails of the list
	 std::shared_ptr<SnakeSegment> m_head = nullptr;
	 std::shared_ptr<SnakeSegment> m_tail = nullptr;
};

#endif


//bad but more efficient method for snake movement 

//integrate
/*void Snake_Tick_()
{
	//remove tail
	m_tail = m_tail->Get_Prev_();
	delete m_tail->Get_Next_();
	m_tail->Set_Next_(nullptr);
	//add head
	 SnakeSegment* temp_ = new  SnakeSegment(m_head->Get_Pos_(), m_head->Get_Orig_(), m_head->Get_Dest_());
	m_head->Set_Prev_(temp_);
	temp_->Set_Next_(m_head);
	m_head = temp_;

}
*/