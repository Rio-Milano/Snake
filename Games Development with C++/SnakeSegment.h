#ifndef SNAKESEGMENT_H
#define SNAKESEGMENT_H

#include <SFML/Graphics.hpp>

	class SnakeSegment
	{

	public:
		//ctors and dtors
		explicit SnakeSegment(const sf::Vector2f& pos_, const sf::Vector2f& orig_, const sf::Vector2f& dest_)
			: pos_(pos_), orig_(orig_), dest_(dest_) {};
		
		~SnakeSegment() {};

		//set the position of the snake segment
		inline void Set_Pos_(const sf::Vector2f& pos_) { this->pos_ = pos_; };

		//set the origin of a snake segment
		inline void Set_Orig_(const sf::Vector2f& orig_) { this->orig_ = orig_; };

		//set the destination of a snake segment
		inline void Set_Dest_(const sf::Vector2f& dest_) { this->dest_ = dest_; };

		//get the position of the snake segment
		inline const sf::Vector2f& Get_Pos_() const { return this->pos_; };
		
		//get the origin of a snake segment
		inline const sf::Vector2f& Get_Orig_() const { return this->orig_; };
		
		//get the destination of a snake segment
		inline const sf::Vector2f& Get_Dest_() const { return this->dest_; };

		//get the right adjacent snake segment
		inline std::shared_ptr<SnakeSegment> Get_Next_()const { return this->m_next; }

		//set the right adjacent snake segment
		inline void Set_Next_(std::shared_ptr<SnakeSegment> segment_) { this->m_next = segment_; }

		//get the left adjacent snake segment
		inline std::shared_ptr<SnakeSegment> Get_Prev_() const{ return this->m_prev; }

		//set the left adjacent snake segment
		inline void Set_Prev_(std::shared_ptr<SnakeSegment> segment_) { this->m_prev = segment_; }

	private:
		//position of the segment
		sf::Vector2f pos_{ 0, 0 };

		//origin of the segment
		sf::Vector2f orig_{ 0, 0 };

		//destination of the segment
		sf::Vector2f dest_{ 0, 0 };
		
		//the pointers for adjacent segments 
		std::shared_ptr<SnakeSegment> m_next = nullptr;
		std::shared_ptr<SnakeSegment> m_prev = nullptr;

	};
#endif
