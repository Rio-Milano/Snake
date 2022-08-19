#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include<vector>
#include<string>

	class Animation
	{
	public:
		//ctors and dtors
		explicit Animation(const sf::Vector2f& scale_, const sf::Vector2f& position_, const int& animation_count_);
		~Animation();

		//draw frame to window
		void Render_();

		//update the animation
		void Update_();


	private:
		//frame of the animation
		int animation_index_ { 0 };

		//the frame of the animation to draw
		sf::Sprite sprite_;

		//the size of the animation
		sf::Vector2f scale_;

		//the position of animation
		sf::Vector2f position_;

		//the frames in the animation 
		int animation_count_ { 0 };
	};

#endif