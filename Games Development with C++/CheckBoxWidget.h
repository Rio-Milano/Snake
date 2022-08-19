#ifndef CHECKBOXWIDGET_T
#define CHECKBOXWIDGET_T

#include <SFML/Graphics.hpp>

	class CheckBoxWidget
	{
	public:
		//ctor and dtor
		explicit CheckBoxWidget
		(
			const sf::Vector2f& position_,
			const sf::Vector2f& size_ = { 540, 146 }
		);
		
		~CheckBoxWidget();

		/*
		
		utility functions

		*/

		//get is the checkbox toggled 
		inline const bool Get_Is_Toggled_(){ return On_Off; };

		//draw the checkbox to the window
		void Render();

		//update the checkbox
		void Update();

		//get if the checkbox is clicked
		const bool Get_Is_Clicked_(const bool& play_sound_ = true);

		//reset the attributes of the checkbox
		void Reset_CheckBox_();



	private:
		/*
		
		utility function

		*/

		//get is the mouse over the checkbox 
		const bool mouse_over_checkbox_(const sf::Vector2f&);

		//get is the checkbox ignoring input
		bool check_box_locked = false;

		//outer layer of the checkbox
		sf::RectangleShape check_box_rect_;
		
		//inner layer of the checkbox
		sf::RectangleShape inner_box_rect;

		//is the checkbox toggled
		bool On_Off = false;


	};

#endif