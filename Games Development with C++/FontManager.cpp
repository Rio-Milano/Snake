#include "FontManager.h"
#include <direct.h>

//ctors and dtors
 FontManager::FontManager()
{
	 //load font into memory
	Add_Font_("Assets_/Fonts_/Bubblegum", ".ttf", "ButtonText");
	Add_Font_("Assets_/Fonts_/BadlyStamped", ".otf", "BadlyStamped");
}

 FontManager::~FontManager()
{
}


//get the one instance of texture manager
 FontManager&  FontManager::Instance_()
{
	 //one instance of texture manager
	static FontManager font_manager_;

	//return one instance of texture manager
	return font_manager_;
}


//add a font by name
void  FontManager::Add_Font_(const std::string& file_name_, const std::string& file_type_, const std::string& font_name_)
{
	//create a font object
	std::shared_ptr<sf::Font> font_ = std::make_shared<sf::Font>();

	//load a font into that object
	font_->loadFromFile(file_name_ + file_type_);

	//add that font to the hash map
	map_of_fonts_[font_name_] = font_;
}
