#include "Text.h"

#include "Window.h"
#define Window  Window::Instance_()
#include"FontManager.h"
#define FontManager  FontManager::Instance_()

Text::Text(std::string text_, sf::Vector2f pos_, int transparancy_scale_, float size_scale_, const unsigned int& size_, const sf::Color& color_) : transparancy_scale_(transparancy_scale_), size_scale_(size_scale_)
{
	this->text_.setString(text_);
	this->text_.setPosition(pos_);
	this->text_.setFont(FontManager.Get_Font_("BadlyStamped"));
	this->text_.setScale({ 1.75, 1.75 });
	this->text_.setOrigin(20, 20);
	this->text_.setCharacterSize(size_);
	this->text_.setFillColor(color_);
}

 Text::~Text()
{
}

void  Text::Render_()
{
	//if the scale of the text is still visible
	if (this->text_.getScale().x > 0.1 && transparancy_ >= 1)
	{
		//get the color of the text
		sf::Color c_color = this->text_.getFillColor();
		
		//adjust the transparancy and see if its more than 0
		if (c_color.a - transparancy_scale_ > 0)
		{
			//set the transparancy 
			c_color.a = c_color.a - transparancy_scale_;

			//update the color of the text
			this->text_.setFillColor(c_color);
		}
		//render the text
		Window.Render_Window_Entity_(text_);

		//update the scale of the text
		this->text_.setScale({float(this->text_.getScale().x - size_scale_ ), float(this->text_.getScale().y - size_scale_)});
	}
	

}

void  Text::Update_()
{

}


