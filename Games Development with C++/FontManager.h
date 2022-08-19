#ifndef FontManager_H
#define FontManager_H

#include<SFML/Graphics.hpp>
#include<unordered_map>
#include<string>

/*

this class embraces the flyweight pattern and encapsulates all the fonts used in the game into one class

*/

class FontManager
{
public:
	
	//gets the instance of the texture manager
	static FontManager& Instance_();

	//get a font by name
	inline const sf::Font& Get_Font_  (std::string font_) {	return *map_of_fonts_[font_];};
		
	//setter functions
	void Add_Font_(const std::string& file_name_, const std::string& file_type_, const std::string& font_name_);

private:
	//ctors and dtors
	FontManager();
	~FontManager();

	//hash map used to map names of font to their font objects 
	std::unordered_map<std::string, std::shared_ptr<sf::Font>> map_of_fonts_;
};

#endif