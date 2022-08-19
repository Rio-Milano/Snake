#include"DoublyLinkedList.h"


//Utility functions
void DoublyLinkedList::Add_Segment_()
{
	//define a new segment
	 std::shared_ptr<SnakeSegment> new_seg_ = std::make_shared<SnakeSegment>(m_tail->Get_Pos_(), m_tail->Get_Orig_(), m_tail->Get_Dest_());
	
	//set the tails next pointer = to the new segment
	m_tail->Set_Next_(new_seg_);

	//set the previous pointer of the new segment to the current tail
	new_seg_->Set_Prev_(m_tail);

	//update the tail to the new segment
	m_tail = new_seg_;
}

void DoublyLinkedList::Add_After_Node_N_(const std::shared_ptr<SnakeSegment>& N, const std::shared_ptr<SnakeSegment>& new_N)
{
	//set the previous segment of the new segment to the segment before where new needs to be
	new_N->Set_Prev_(N);

	//set the next segment of the new segment to the next of the segment that will be before new segment 
	new_N->Set_Next_(N->Get_Next_());

	//next of old segment needs to point to new segment
	N->Get_Next_()->Set_Prev_(new_N);

	//the next of old segment needs to point to new segment 
	N->Set_Next_(new_N);
}

void DoublyLinkedList::Add_Segment_At_Point_(const sf::Vector2f& pos_, const sf::Vector2f& orig_, const sf::Vector2f& dest_)
{
	//create a new segment bassed on params passed
	 std::shared_ptr<SnakeSegment> new_seg_ = std::make_shared<SnakeSegment>(pos_, orig_, dest_);

	//if list is empty then set head and tail of list to new segment
	if (m_head == nullptr)
	{
		m_head = new_seg_;
		m_tail = new_seg_;
	}
	else
	{//if list is not empy

		//set the previous pointer of the new segment to the current tail
		new_seg_->Set_Prev_(m_tail);

		//set the next pointer of the current tail to the new segment
		m_tail->Set_Next_(new_seg_);

		//update the tail to the new segment
		m_tail = new_seg_;
	}
};;